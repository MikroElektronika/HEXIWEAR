#!/usr/bin/python3
"""
/*!
* Copyright (c) 2015, Freescale Semiconductor, Inc.
* All rights reserved.
* \file otaps.py
* This file is the source file for the BLE OTAP Server PC application
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

This script runs a FSL BLE OTAP Server using a provided .srec image,
an image configuration file and an optional serial configuration file.
How to use this script:
"c:\Python34\python.exe" otaps.py imagename.srec imgconfig.json

Press CTRL+C to stop the script any time. """

import sys
import signal
import glob
import json
import pprint
from threading import Timer
import time
import os
import array
import binascii
import serial
import serial.tools.list_ports
import string


expectedNumberOfArguments = 2;

# FSCI commands
gFsciBleOtapOpcodeGroup_c = 0x4F

gOtapCmdIdNoCommand_c               = 0x00
gOtapCmdIdNewImageNotification_c    = 0x01
gOtapCmdIdNewImageInfoRequest_c     = 0x02
gOtapCmdIdNewImageInfoResponse_c    = 0x03
gOtapCmdIdImageBlockRequest_c       = 0x04
gOtapCmdIdImageChunk_c              = 0x05
gOtapCmdIdImageTransferComplete_c   = 0x06
gOtapCmdIdErrorNotification_c       = 0x07
gOtapCmdIdStopImageTransfer_c       = 0x08

gOtap_ImageIdFieldSize_c            = 2 #bytes
gOtap_ImageVersionFieldSize_c       = 8 #bytes
gOtap_CmdIdFieldSize_c              = 1
gOtap_ImageFileSizeFieldSize_c      = 4

gOtap_StartPositionFieldSize_c      = 4
gOtap_BlockSizeFieldSize_c          = 4
gOtap_ChunkSizeFieldSize_c          = 2
gOtap_TransferMethodFieldSize_c     = 1
gOtap_L2capChannelOrPsmFieldSize_c  = 2

gOtap_SeqNumberFieldSize_c          = 1
gOtap_MaxNumberOfChunksperBlock_c   = 256

gOtap_ImageChunkDataSizeAtt_c       = 20 - gOtap_CmdIdFieldSize_c - gOtap_SeqNumberFieldSize_c

gOtap_StatusFieldSize_c             = 1

#serial protocol constants
fsciSync = 0x02
fsciSyncPos = 0
fsciSyncLen = 1
fsciOpGroupPos = 1
fsciOpGroupLen = 1
fsciOpcodePos = 2
fsciOpcodeLen = 1
fsciDataLengthPos = 3
fsciDataLengthLen = 2
fsciDataPos = 5
fsciCrcLen = 1

# OTAP FSCI related command lengths
gFsciOtapCmdFixedLength                     = fsciSyncLen + fsciOpGroupLen + fsciOpcodeLen + fsciDataLengthLen + fsciCrcLen;
    
gFsciOtapCmdIdNoCommandLength               = 0
gFsciOtapCmdIdNewImageNotificationLength    = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c + gOtap_ImageVersionFieldSize_c + gOtap_ImageFileSizeFieldSize_c;
gFsciOtapCmdIdNewImageInfoRequestLength     = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c + gOtap_ImageVersionFieldSize_c;
gFsciOtapCmdIdNewImageInfoResponseLength    = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c + gOtap_ImageVersionFieldSize_c + gOtap_ImageFileSizeFieldSize_c;
gFsciOtapCmdIdImageBlockRequestLength       = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c + gOtap_StartPositionFieldSize_c + gOtap_BlockSizeFieldSize_c + gOtap_ChunkSizeFieldSize_c + gOtap_TransferMethodFieldSize_c + gOtap_L2capChannelOrPsmFieldSize_c;
gFsciOtapCmdIdImageChunkAttLength           = gFsciOtapCmdFixedLength + gOtap_SeqNumberFieldSize_c + gOtap_ImageChunkDataSizeAtt_c;
gFsciOtapCmdIdImageTransferCompleteLength   = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c + gOtap_StatusFieldSize_c;
gFsciOtapCmdIdErrorNotificationLength       = gFsciOtapCmdFixedLength + fsciOpcodeLen + gOtap_StatusFieldSize_c;
gFsciOtapCmdIdStopImageTransferLength       = gFsciOtapCmdFixedLength + gOtap_ImageIdFieldSize_c;

# image file related variables
currentImageId = 0x0002;
expectedInputImageFileExtension = '.srec';
serialConfigFileName = 'serialconfig.json';
expectedImageFileCrcSize = 2;
imageIdLength = 0 # in bytes - will be initialized from the configuration file
imageFileSizeLength = 0 # in bytes - will be initialized from the configuration file

# image file sub elements
imageSubElementType = 0x0000;
imageSectorBitmapSubElementType = 0xF000;
imageFileCrcSubElementType = 0xF100;
subElementTypeSize = 2;
subElementLengthSize = 4;

timeToSendChunk = False
chunkIntervalSec = 0.1

def signal_handler(signal, frame):
    print("Program interrupted via CTRL+C")
    sys.exit(0)

def otaps(argv):
    
    # Register the signal handler for SIGINT
    signal.signal(signal.SIGINT, signal_handler)
    
    # Check the number of arguments
    if len(argv) != expectedNumberOfArguments:
        print("Error: Invalid number of arguments, got ", str(len(argv)), ", expected ", str(expectedNumberOfArguments), sep='');
        sys.exit(1);

    # Open the executable image file and the image configuration file
    print("Opening executable image file:", argv[0], "...");
    try:
        imgFile = open(argv[0], 'r')
    except Exception as e:
        print("Error: Could not open executable image file ", argv[0], sep='');
        sys.exit(1);

    inputImgFname, inputImgFext = os.path.splitext(argv[0]);
    if (inputImgFext.lower() != expectedInputImageFileExtension.lower()):
        print("Warning: The input executable image file does not have the expected extension, got ", inputImgFext, ", expected ", expectedInputImageFileExtension.lower(), sep='')

    print("Opening image configuration file:", argv[1], "...");
    try:
        imgConfigFile = open(argv[1], 'r')
    except Exception as e:
        print("Error: Could not open image configuration file ", argv[1], sep='');
        sys.exit(1);

    # Load data from the image configuration file and close it
    print("Loading data from image configuration file:", argv[1], "...");
    try:
        imgConfig = json.load(imgConfigFile)
    except Exception as e:
        print("Error: Error loading data from image configuration file ", argv[1], sep='');
        sys.exit(1);

    imgConfigFile.close()

    # Open the output file for binary writing
    outputFname = inputImgFname + "_" + time.strftime("%Y%m%d_%H%M%S") + ".img";
    print("Opening output image file for writing:", outputFname, "...");
    try:
        imgOutputFile = open(outputFname, 'wb+')
    except Exception as e:
        print("Error: Could not open output image file ", outputFname, sep='');
        sys.exit(1);

    # ================================================================================
    # Parse the image configuration data and build the image file binary header
    print("Parsing the image configuration file and building the image file header...");

    binaryHeaderDict = buildImgFileHeader(imgConfig);

    if (binaryHeaderDict["hdrBuildSuccess"] != True):
        print("Error: The image file header could not be built.");
        sys.exit(1);

    # Check if the header contains valid information about the image id and image file size
    if ("imgIdPos" not in binaryHeaderDict.keys()) or ("imgIdLen" not in binaryHeaderDict.keys()):
        print("Error: The image file header does not contain the expected Image Id information.");
        sys.exit(1);

    if (binaryHeaderDict["imgIdPos"] == 0) or (binaryHeaderDict["imgIdLen"] == 0):
        print("Error: The image file header Image Id information is not valid.");
        sys.exit(1);

    if ("imgFileSizePos" not in binaryHeaderDict.keys()) or ("imgFileSizeLen" not in binaryHeaderDict.keys()):
        print("Error: The image file header does not contain the expected Image File Size information.");
        sys.exit(1);

    if (binaryHeaderDict["imgFileSizePos"] == 0) or (binaryHeaderDict["imgFileSizeLen"] == 0):
        print("Error: The image file header Image File Size information is not valid.");
        sys.exit(1);
    
    imageIdLength = binaryHeaderDict["imgIdLen"];
    if (gOtap_ImageIdFieldSize_c != imageIdLength):
        print("Error: The image id field size read from the image configuration file does not match the image id filed size expected over the air.");
        sys.exit(1);
    imageFileSizeLength = binaryHeaderDict["imgFileSizeLen"];
    if (gOtap_ImageFileSizeFieldSize_c != imageFileSizeLength):
        print("Error: The image size field size read from the image configuration file does not match the image size filed size expected over the air.");
        sys.exit(1);
    pprint.pprint(binaryHeaderDict)
    print ("Size of binary header:", len(binaryHeaderDict["binaryHeader"]), ", reported written length:", binaryHeaderDict["writtenLen"])

    # Insert the current image Id in the image header
    #binaryHeaderDict["imageId"] = currentImageId;
    currentImageId = binaryHeaderDict["imageId"];
    print ("Inserting image id ", format(currentImageId, '#06x'), " into binary image header...", sep='')
    insertIntValueIntoBinaryArray (binaryHeaderDict["binaryHeader"], currentImageId, binaryHeaderDict["imgIdPos"], binaryHeaderDict["imgIdLen"]);

    print ("binaryHeader", ":", binaryHeaderDict["binaryHeader"])
    print ("imgIdPos", ":", binaryHeaderDict["imgIdPos"])
    print ("imgIdLen", ":", binaryHeaderDict["imgIdLen"])
    print ("imgId", ":", binaryHeaderDict["imageId"])
    print ("Size of binary header:", len(binaryHeaderDict["binaryHeader"]), ", reported written length:", binaryHeaderDict["writtenLen"])

    # ================================================================================
    # Parse the executable image file and build the image sub-element
    print("Parsing executable image file and building the image sub-element...");

    binaryImageSubElemDict = buildImageSubElement(imgFile);
    imgFile.close();
    
    if (binaryImageSubElemDict["imgSubElemBuildSuccess"] != True):
        print("Error: The image sub-element could not be built.");
        sys.exit(1);
        
    for key in sorted(binaryImageSubElemDict.keys()):
        if key != "binaryImgSubElem":
            print(key, ":", binaryImageSubElemDict[key])
        else:
            if len(binaryImageSubElemDict["binaryImgSubElem"]) < 133:
                print("binaryImgSubElem", ":", binaryImageSubElemDict["binaryImgSubElem"])
            else:
                print("binaryImgSubElem", ":", binaryImageSubElemDict["binaryImgSubElem"][0:133], "... ... ...")

    print ("Size of binary image sub-element:",
           len(binaryImageSubElemDict["binaryImgSubElem"]),
           ", reported written length:",
           binaryImageSubElemDict["imgSubElemWrittenLen"]);
    print ("Actual binary image size:",
           len(binaryImageSubElemDict["binaryImgSubElem"]) - subElementTypeSize - subElementLengthSize)
    
    # ================================================================================
    # Parse the image configuration data and build the image sector bitmap sub-element
    print("Parsing image configuration data and building the image sector bitmap sub-element...");
    
    binaryImageSectorBitmapDict = buildImgSectorBitmapSubElement(imgConfig);
    
    if (binaryImageSectorBitmapDict["imgSectBitmapSubElemBuildSuccess"] != True):
        print("Error: The image sector bitmap sub-element could not be built.");
        sys.exit(1);
    
    pprint.pprint(binaryImageSectorBitmapDict)
    print ("Size of binary image sector bitmap sub-element:", \
           len(binaryImageSectorBitmapDict["binaryImgSectBitmapSubElem"]), \
           ", reported written length:", \
           binaryImageSectorBitmapDict["imgSectBitmapSubElemWrittenLen"]);
    print ("Actual binary image sector bitmap size:",
           len(binaryImageSectorBitmapDict["binaryImgSectBitmapSubElem"]) - subElementTypeSize - subElementLengthSize);
    
    # ================================================================================
    # Parse the image configuration data and build the image file CRC sub-element
    print("Parsing image configuration data and building the image file CRC sub-element...");
    
    binaryImageFileCrcDict = buildImgFileCrcSubElement(imgConfig);
    
    if (binaryImageFileCrcDict["imgFileCrcSubElemBuildSuccess"] != True):
        print("Error: The image file CRC sub-element could not be built.");
        sys.exit(1);
        
    if (len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]) - subElementTypeSize - subElementLengthSize) != expectedImageFileCrcSize:
        print("Error: The image file CRC size is not valid, got ", \
              len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]) - subElementTypeSize - subElementLengthSize, \
              " expected ", \
              expectedImageFileCrcSize, sep='');
        sys.exit(1);
        
    pprint.pprint(binaryImageFileCrcDict)
    
    print ("Size of binary image file CRC sub-element:", \
           len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]), \
           ", reported written length:", \
           binaryImageFileCrcDict["imgFileCrcSubElemWrittenLen"]);
    print ("Actual binary image file CRC size:",
           len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]) - subElementTypeSize - subElementLengthSize);
    
    # ================================================================================
    # Compute the total image file size and insert it into the header.
    print("Computing the total image file size and inserting it into the header...");
    
    totalImageFileSize = len (binaryHeaderDict["binaryHeader"]) + \
                         len (binaryImageSubElemDict["binaryImgSubElem"]) + \
                         len (binaryImageSectorBitmapDict["binaryImgSectBitmapSubElem"]) + \
                         len (binaryImageFileCrcDict["binaryImgFileCrcSubElem"]);
    print ("The total image file size is:", totalImageFileSize)
    
    print ("Inserting total image file size ", format(totalImageFileSize, '#06x'), " into binary image header...", sep='')
    insertIntValueIntoBinaryArray (binaryHeaderDict["binaryHeader"], \
                                   totalImageFileSize, \
                                   binaryHeaderDict["imgFileSizePos"], \
                                   binaryHeaderDict["imgFileSizeLen"]);

    print ("binaryHeader", ":", binaryHeaderDict["binaryHeader"])
    print ("imgFileSizePos", ":", binaryHeaderDict["imgFileSizePos"])
    print ("imgFileSizeLen", ":", binaryHeaderDict["imgFileSizeLen"])
    print ("Size of binary header:", len(binaryHeaderDict["binaryHeader"]), ", reported written length:", binaryHeaderDict["writtenLen"])
    
    # ================================================================================
    # Compute the image file CRC and insert it into the appropriate sub-element.
    print("Computing the image file CRC and inserting it into the appropriate sub-element...");
    imageFileCrc = imgConfig["imageFileCrcInitialValue"];
    
    startTime = time.time()
    imageFileCrc = crcCompute (binaryHeaderDict["binaryHeader"], \
                                        imageFileCrc);
    imageFileCrc = crcCompute (binaryImageSubElemDict["binaryImgSubElem"], \
                                        imageFileCrc);
    imageFileCrc = crcCompute (binaryImageSectorBitmapDict["binaryImgSectBitmapSubElem"], \
                                        imageFileCrc);
    endTime = time.time()
    print ("Image file CRC Computation took:", endTime - startTime, "seconds")

    print ("The computed CRC is:", format(imageFileCrc, '#06x'));
    print ("Inserting the computed CRC ", format(imageFileCrc, '#06x'), " into the image file CRC sub-element...", sep='')
    
    #print ("CRC('123456789') = ", format(computeImgFileCrc16 (B'123456789', 0), '#06x')) #expected result 0x31c3
    #print ("CRC('123456789') = ", format(crcCompute (B'123456789', 0), '#06x')) #expected result 0x31c3
    insertIntValueIntoBinaryArray (binaryImageFileCrcDict["binaryImgFileCrcSubElem"], \
                                   imageFileCrc, \
                                   subElementTypeSize + subElementLengthSize, \
                                   expectedImageFileCrcSize);
                                   
    pprint.pprint(binaryImageFileCrcDict)
    
    print ("Size of binary image file CRC sub-element:", \
           len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]), \
           ", reported written length:", \
           binaryImageFileCrcDict["imgFileCrcSubElemWrittenLen"]);
    print ("Actual binary image file CRC size:",
           len(binaryImageFileCrcDict["binaryImgFileCrcSubElem"]) - subElementTypeSize - subElementLengthSize);
    
    # ================================================================================
    # Create the output image file and write it to the output file
    print("Creating the output image file and writing it to the output file...");
    
    imageFileInternal = array.array ('B');
    imageFileInternal.extend (binaryHeaderDict["binaryHeader"]);
    imageFileInternal.extend (binaryImageSubElemDict["binaryImgSubElem"]);
    imageFileInternal.extend (binaryImageSectorBitmapDict["binaryImgSectBitmapSubElem"]);
    imageFileInternal.extend (binaryImageFileCrcDict["binaryImgFileCrcSubElem"]);
    
    if (len(imageFileInternal) != totalImageFileSize):
        print("Error: The created image file size does not match the previously calculated value, got", \
              len(imageFileInternal), \
              "expected", \
              totalImageFileSize);
        sys.exit(1);
        
    print ("Created output image file internal with size", len(imageFileInternal), "as expected");
    
    try:
        imageFileInternal.tofile(imgOutputFile);
    except Exception as e:
        print("Error: Could not write image to output file ", imgOutputFile.name);
        sys.exit(1);
        
    try:
        outputFileSize = os.stat(imgOutputFile.name).st_size;
    except Exception as e:
        print("Error: Could not get written output file size for", imgOutputFile.name);
        sys.exit(1);
    
    if (outputFileSize != totalImageFileSize):
        print("Error: The size of the written image file does not match the previously calculated value, got", \
              outputFileSize, \
              "expected", \
              totalImageFileSize);
        sys.exit(1);
        
    print ("Successfully written output image file with size", outputFileSize, "as expected");
    
    imgOutputFile.close()
    
    # ================================================================================
    # Look for the serial configuration file and if not present look for ports and build one using user input
    print("Getting the serial configuration ...");
    serialConfigDict = getSerialConfiguration ();
    print("Serial configuration obtained:");
    pprint.pprint (serialConfigDict)
    
    print("Trying to open the serial port with set baudrate and 8 N 1, no handshaking...");
    rtsCtsConfig = False;
    try:
        serverSer = serial.Serial (port = serialConfigDict["port"],
                                   baudrate = serialConfigDict["baudrate"],
                                   bytesize = serial.EIGHTBITS,
                                   parity = serial.PARITY_NONE,
                                   stopbits = serial.STOPBITS_ONE,
                                   rtscts = rtsCtsConfig);
    except Exception as e:
        print("Error: Could not open the serial communication port.");
        sys.exit(1);
        
    print ("Serial port", serialConfigDict["port"], "successfully open.");
    
    # ================================================================================
    # Run the OTAP Server on the selected serial port
    runOtapServer (serverSer, imageFileInternal, currentImageId, binaryHeaderDict["imgFileVersion"]);
    
    serverSer.close();

    print ("Program completed normally");

# ================================================================================================================================================
# ================================================================================================================================================
def runOtapServer (srvSerial, imageFileArray, imgIdNumber, imgVersionString):
    #serverStates = set(["serverStateIdle", "serverStateSendingBlock", "imageTransferComplete"]);
    expectedCmdIds = set(["cmdNone",
                          "cmdNewImageInfoRequest",
                          "cmdImageBlockRequest",
                          "cmdImageTransferComplete",
                          "cmdErrorNotification",
                          "cmdStopImageTransfer"]);
    
    #serverState = "serverStateIdle";
    
    chunkTransferStateDict = { "currentChunkSeqNum":    0,
                               "bytesToSend":           0,
                               "currentPos":            0,
                               "chunkSize":             0
                             };
    
    global chunkIntervalSec
    
    maxKbpsAtt = 4000 # kilo bits per second
    maxKbpsL2cap = 10000 # kilo bits per second
    
    global timeToSendChunk
    
    from time import sleep
    
    def _chunkTimeout():
        global timeToSendChunk
        global chunkIntervalSec
        while True:
            sleep(chunkIntervalSec)
            timeToSendChunk = True
            #print ("Timer expired.")
        
    from threading import Thread
    chunkTimer = Thread(target=_chunkTimeout)
    chunkTimer.daemon = True
    chunkTimer.start()
    
    print ("Waiting for commands from OTAP Client")
    
    #loop until explicit loop "break"
    while True:
        # wait for characters and return a command if a valid command is received and None otherwise
        rxCmd = readSerialCommands (srvSerial);
        
        if rxCmd != None:
            if rxCmd["cmdType"] not in expectedCmdIds:
                print ("Received command dict with unexpected cmdType, ignoring command:")
                print (rxCmd)
            
            #print (rxCmd["cmdType"], rxCmd["params"])
            #print (rxCmd["cmdType"], ":" ,[format(item, '#04X')for item in rxCmd["rawCmd"]])
            
            # handle commands and send responses if necessary
            if   rxCmd["cmdType"] == "cmdNewImageInfoRequest":
                print ("RX>> ", rxCmd["cmdType"], rxCmd["params"])
                # check the command parameters and respond accordingly
                rxCmdParamsValid = True
                if rxCmd["params"]["imageId"] != 0x0000: #current image id should be 0x0000
                    rxCmdParamsValid = False
                    txCmdArray = buildFsciOtapCmdErrorNotification (gOtapCmdIdNewImageInfoRequest_c, 0x09);
                    if txCmdArray != None:
                        print ("TX>> ", "cmdErrorNotification", ":" ,[format(item, '#04X') for item in txCmdArray])
                        writeSerialCommand (srvSerial, txCmdArray);
                    else:
                        print ("Error: could not build serial command.")
                        sys.exit(1)
                        
                if rxCmdParamsValid == True:
                    if rxCmd["params"]["imageVersion"].lower() == "0xFFFFFFFFFFFFFFFF".lower():
                        #all images on the server have been requested
                        txCmdArray = buildFsciOtapCmdNewImageInfoResponse (imgIdNumber, imgVersionString, len(imageFileArray));    
                        if txCmdArray != None:
                            print ("TX>> ", "cmdNewImageInfoResponse", ":" ,[format(item, '#04X') for item in txCmdArray])
                            writeSerialCommand (srvSerial, txCmdArray);
                        else:
                            print ("Error: could not build serial command.")
                            sys.exit(1)
                    else:
                        #respond anyway - the client will choose to download the image or not based on the image version
                        txCmdArray = buildFsciOtapCmdNewImageInfoResponse (imgIdNumber, imgVersionString, len(imageFileArray));    
                        if txCmdArray != None:
                            print ("TX>> ", "cmdNewImageInfoResponse", ":" ,[format(item, '#04X') for item in txCmdArray])
                            writeSerialCommand (srvSerial, txCmdArray);
                        else:
                            print ("Error: could not build serial command.")
                            sys.exit(1)
                        
            elif rxCmd["cmdType"] == "cmdImageBlockRequest":
                print ("RX>> ", rxCmd["cmdType"], rxCmd["params"])
                # stop current block transfer if in progress
                if chunkTransferStateDict["bytesToSend"] != 0:
                    print ("  >> ", "Stopping the current block transfer. Last position:",
                           chunkTransferStateDict["currentPos"],
                           "out of",
                           len(imageFileArray))
                    chunkTransferStateDict["bytesToSend"] = 0; 
                    
                # check the command parameters and respond accordingly
                rxCmdParamsValid = True
                if rxCmd["params"]["imageId"] != 0x0002 or \
                   rxCmd["params"]["startPosition"] >= len(imageFileArray) or \
                   (rxCmd["params"]["startPosition"] + rxCmd["params"]["blockSize"]) > len(imageFileArray) or \
                   (rxCmd["params"]["chunkSize"] * gOtap_MaxNumberOfChunksperBlock_c) < rxCmd["params"]["blockSize"] or \
                   (rxCmd["params"]["transferMethod"] == 0x00 and rxCmd["params"]["chunkSize"] > gOtap_ImageChunkDataSizeAtt_c) or \
                   (rxCmd["params"]["transferMethod"] == 0x00 and rxCmd["params"]["l2capChannelOrPsm"] != 0x0004) or \
                   (rxCmd["params"]["transferMethod"] == 0x01 and (rxCmd["params"]["l2capChannelOrPsm"] < 0x0040 or rxCmd["params"]["l2capChannelOrPsm"] > 0x007F)) or \
                   rxCmd["params"]["transferMethod"] > 0x01:
                    rxCmdParamsValid = False
                    txCmdArray = buildFsciOtapCmdErrorNotification (gOtapCmdIdImageBlockRequest_c, 0x09);
                    if txCmdArray != None:
                        print ("TX>> ", "cmdErrorNotification", ":" ,[format(item, '#04X') for item in txCmdArray])
                        writeSerialCommand (srvSerial, txCmdArray);
                    else:
                        print ("Error: could not build serial command.")
                        sys.exit(1)
                        
                if rxCmdParamsValid == True:                        
                    #set up the server to send the chunks
                    chunkTransferStateDict["currentChunkSeqNum"] = 0;
                    chunkTransferStateDict["bytesToSend"] = rxCmd["params"]["blockSize"];
                    chunkTransferStateDict["currentPos"] = rxCmd["params"]["startPosition"];
                    chunkTransferStateDict["chunkSize"] = rxCmd["params"]["chunkSize"];
                    print ("Sending requested data block...")
                    if rxCmd["params"]["transferMethod"] == 0:      # ATT transfer method
                        chunkIntervalSec = 1 / (maxKbpsAtt / (rxCmd["params"]["chunkSize"] * 8));
                    elif rxCmd["params"]["transferMethod"] == 1:    # L2CAP transfer method
                        chunkIntervalSec = 1 / (maxKbpsL2cap / (rxCmd["params"]["chunkSize"] * 8));
                    if rxCmd["params"]["startPosition"] == 0:
                        imageStartTime = time.time();
                    timeToSendChunk = False
                    blockStartTime = time.time()

            elif rxCmd["cmdType"] == "cmdImageTransferComplete":
                print ("RX>> ", rxCmd["cmdType"], rxCmd["params"])
                if rxCmd["params"]["status"] == 0x00: #0x00 = success
                    print ("Stopping the OTAP server");
                    imageEndTime = time.time();
                    break #exit the while loop
                else:
                    if chunkTransferStateDict["bytesToSend"] != 0:
                        print ("  >> ", "Stopping the current block transfer. Last byte:",
                               chunkTransferStateDict["currentPos"],
                               "out of",
                               len(imageFileArray))
                        chunkTransferStateDict["bytesToSend"] = 0;
            elif rxCmd["cmdType"] == "cmdErrorNotification":
                print ("RX>> ", rxCmd["cmdType"], rxCmd["params"])
                if chunkTransferStateDict["bytesToSend"] != 0:
                    print ("  >> ", "Stopping the current block transfer. Last byte:",
                           chunkTransferStateDict["currentPos"],
                           "out of",
                           len(imageFileArray))
                    chunkTransferStateDict["bytesToSend"] = 0;
            elif rxCmd["cmdType"] == "cmdStopImageTransfer":
                print ("RX>> ", rxCmd["cmdType"], rxCmd["params"])
                if chunkTransferStateDict["bytesToSend"] != 0:
                    print ("  >> ", "Stopping the current block transfer. Last byte:",
                           chunkTransferStateDict["currentPos"],
                           "out of",
                           len(imageFileArray))
                    chunkTransferStateDict["bytesToSend"] = 0;
            else:
                print ("Warning: Received unhandled command:")
                print ("RX>> ", rxCmd)
                print ("  >> ", rxCmd["cmdType"], ":" ,[format(item, '#04X') for item in rxCmd["rawCmd"]])
        
        if chunkTransferStateDict["bytesToSend"] == 0:
            timeToSendChunk = True
 
        # send image chunks if required
        if (chunkTransferStateDict["bytesToSend"] != 0) and (timeToSendChunk == True):
            if chunkTransferStateDict["bytesToSend"] < chunkTransferStateDict["chunkSize"]:
                start = chunkTransferStateDict["currentPos"];
                end = chunkTransferStateDict["currentPos"] + chunkTransferStateDict["bytesToSend"];
                txCmdArray = buildFsciOtapCmdImageChunk (chunkTransferStateDict["currentChunkSeqNum"], imageFileArray[start:end]);
            else:
                start = chunkTransferStateDict["currentPos"];
                end = chunkTransferStateDict["currentPos"] + chunkTransferStateDict["chunkSize"];
                txCmdArray = buildFsciOtapCmdImageChunk (chunkTransferStateDict["currentChunkSeqNum"], imageFileArray[start:end]);
            
            chunkTransferStateDict["bytesToSend"] -= (end - start);
            chunkTransferStateDict["currentPos"] += (end - start);
            chunkTransferStateDict["currentChunkSeqNum"] += 1;
                
            if txCmdArray != None:
                if chunkTransferStateDict["currentChunkSeqNum"] < 2:
                    print ("TX>> ", "cmdImageChunk", ":" ,[format(item, '#04X') for item in txCmdArray])
                writeSerialCommand (srvSerial, txCmdArray);
                timeToSendChunk = False
            else:
                print ("Error: could not build serial command.")
                sys.exit(1)
                
            if chunkTransferStateDict["bytesToSend"] == 0:
                print ("Finished sending requested data block ending at byte",
                       chunkTransferStateDict["currentPos"],
                       "out of",
                       len(imageFileArray))
                blockEndTime = time.time()
                print ("Block transmission time:", blockEndTime - blockStartTime, "seconds")
                
    print ("Image transmission time:", imageEndTime - imageStartTime, "seconds")
    return

# ================================================================================================================================================
# ================================================================================================================================================
def buildFsciOtapCmdNewImageNotification (imageIdNumber, imgVersionString, imageFileLength):
    cmdArray = array.array('B');
    cmdArray.extend(fsciSync.to_bytes(fsciSyncLen, byteorder="little"));
    cmdArray.extend(gFsciBleOtapOpcodeGroup_c.to_bytes(fsciOpGroupLen, byteorder="little"));
    cmdArray.extend(gOtapCmdIdNewImageNotification_c.to_bytes(fsciOpcodeLen, byteorder="little"));
    
    cmdArray.extend((gFsciOtapCmdIdNewImageNotificationLength - gFsciOtapCmdFixedLength).to_bytes(fsciDataLengthLen, byteorder="little"));
    
    cmdArray.extend(imageIdNumber.to_bytes(gOtap_ImageIdFieldSize_c, byteorder="little"));
    cmdArray.extend(array.array('B',int(imgVersionString, 16).to_bytes(gOtap_ImageVersionFieldSize_c, byteorder='little')));
    cmdArray.extend(imageFileLength.to_bytes(gOtap_ImageFileSizeFieldSize_c, byteorder="little"));
    
    crc = 0;
    for byte in cmdArray[1:]:
        crc = crc ^ byte;
        
    cmdArray.extend(crc.to_bytes(fsciCrcLen, byteorder="little"));
    
    #print ([format(item, '#04X') for item in cmdArray])
    return cmdArray
    
# ================================================================================================================================================
# ================================================================================================================================================
def buildFsciOtapCmdNewImageInfoResponse (imageIdNumber, imgVersionString, imageFileLength):
    cmdArray = array.array('B');
    cmdArray.extend(fsciSync.to_bytes(fsciSyncLen, byteorder="little"));
    cmdArray.extend(gFsciBleOtapOpcodeGroup_c.to_bytes(fsciOpGroupLen, byteorder="little"));
    cmdArray.extend(gOtapCmdIdNewImageInfoResponse_c.to_bytes(fsciOpcodeLen, byteorder="little"));
    
    cmdArray.extend((gFsciOtapCmdIdNewImageInfoResponseLength - gFsciOtapCmdFixedLength).to_bytes(fsciDataLengthLen, byteorder="little"));
    
    cmdArray.extend(imageIdNumber.to_bytes(gOtap_ImageIdFieldSize_c, byteorder="little"));
    cmdArray.extend(array.array('B',int(imgVersionString, 16).to_bytes(gOtap_ImageVersionFieldSize_c, byteorder='little')));
    cmdArray.extend(imageFileLength.to_bytes(gOtap_ImageFileSizeFieldSize_c, byteorder="little"));
    
    crc = 0;
    for byte in cmdArray[1:]:
        crc = crc ^ byte;
        
    cmdArray.extend(crc.to_bytes(fsciCrcLen, byteorder="little"));
    
    #print ([format(item, '#04X') for item in cmdArray])
    return cmdArray

# ================================================================================================================================================
# ================================================================================================================================================
def buildFsciOtapCmdImageChunk (seqNumber, dataArray):
    cmdArray = array.array('B');
    cmdArray.extend(fsciSync.to_bytes(fsciSyncLen, byteorder="little"));
    cmdArray.extend(gFsciBleOtapOpcodeGroup_c.to_bytes(fsciOpGroupLen, byteorder="little"));
    cmdArray.extend(gOtapCmdIdImageChunk_c.to_bytes(fsciOpcodeLen, byteorder="little"));
    
    cmdArray.extend((gOtap_SeqNumberFieldSize_c + len(dataArray)).to_bytes(fsciDataLengthLen, byteorder="little"));
    
    cmdArray.extend(seqNumber.to_bytes(gOtap_SeqNumberFieldSize_c, byteorder="little"));
    cmdArray.extend(dataArray);
    
    crc = 0;
    for byte in cmdArray[1:]:
        crc = crc ^ byte;
        
    cmdArray.extend(crc.to_bytes(fsciCrcLen, byteorder="little"));
    
    #print ([format(item, '#04X') for item in cmdArray])
    return cmdArray
    
# ================================================================================================================================================
# ================================================================================================================================================
def buildFsciOtapCmdErrorNotification (errorCmdId, errorStatus):
    cmdArray = array.array('B');
    cmdArray.extend(fsciSync.to_bytes(fsciSyncLen, byteorder="little"));
    cmdArray.extend(gFsciBleOtapOpcodeGroup_c.to_bytes(fsciOpGroupLen, byteorder="little"));
    cmdArray.extend(gOtapCmdIdErrorNotification_c.to_bytes(fsciOpcodeLen, byteorder="little"));
    
    cmdArray.extend((gFsciOtapCmdIdErrorNotificationLength - gFsciOtapCmdFixedLength).to_bytes(fsciDataLengthLen, byteorder="little"));
    
    cmdArray.extend(errorCmdId.to_bytes(gOtap_CmdIdFieldSize_c, byteorder="little"));
    cmdArray.extend(errorStatus.to_bytes(gOtap_StatusFieldSize_c, byteorder="little"));
    
    crc = 0;
    for byte in cmdArray[1:]:
        crc = crc ^ byte;
        
    cmdArray.extend(crc.to_bytes(fsciCrcLen, byteorder="little"));
    
    #print ([format(item, '#04X') for item in cmdArray])
    return cmdArray

# ================================================================================================================================================
# ================================================================================================================================================    
def writeSerialCommand (srvSerial, txCmdArray):
    try:
        written = srvSerial.write(txCmdArray)
        if written != len(txCmdArray):
            print("Error: Could not write all bytes to the serial port.");
            sys.exit(1);
    except Exception as e:
        print("Error: Could not write to the serial port.");
        sys.exit(1);
    pass
    
# ================================================================================================================================================
# ================================================================================================================================================
def readSerialCommands (srvSerial):
    
    retCmdDict = {"cmdType":    "cmdNone",
                  "params":     {},
                 }
                 
    
    # function statics
    if not hasattr(readSerialCommands, "crc"):
        readSerialCommands.crc = 0
    if not hasattr(readSerialCommands, "receivedBytes"):
        readSerialCommands.receivedBytes = 0
    if not hasattr(readSerialCommands, "dataBytesToReceive"):
        readSerialCommands.dataBytesToReceive = 0
    if not hasattr(readSerialCommands, "rcvCmdBuffer"):
        readSerialCommands.rcvCmdBuffer = array.array('B')
    if not hasattr(readSerialCommands, "rcvCmdState"):
        readSerialCommands.rcvCmdState = "rcvStateWaitingForSync"
    
    receivedValidCommand = False
    
    # Loop while characters are available from the serial interface
    while srvSerial.inWaiting() != 0:
    
        recVal = ord(srvSerial.read())
        
        if readSerialCommands.rcvCmdState == "rcvStateWaitingForSync":
            if recVal == fsciSync:
                # the sync has been received, reinitialize the received cmd array and the CRC
                readSerialCommands.rcvCmdBuffer = array.array('B', recVal.to_bytes(fsciSyncLen, byteorder='little'))
                readSerialCommands.crc = 0; #the sync is not used to compute the CRC
                readSerialCommands.rcvCmdState = "rcvStateWaitingForOG"
            else:
                #framing error, or serial error, reset the received cmd array
                readSerialCommands.crc = 0;
                readSerialCommands.rcvCmdBuffer = array.array('B')
        elif readSerialCommands.rcvCmdState == "rcvStateWaitingForOG":
            readSerialCommands.rcvCmdBuffer.append(recVal)
            readSerialCommands.crc ^= recVal
            readSerialCommands.rcvCmdState = "rcvStateWaitingForOC"
        elif readSerialCommands.rcvCmdState == "rcvStateWaitingForOC":
            readSerialCommands.rcvCmdBuffer.append(recVal)
            readSerialCommands.crc ^= recVal
            readSerialCommands.rcvCmdState = "rcvStateWaitingForDataLength"
        elif readSerialCommands.rcvCmdState == "rcvStateWaitingForDataLength":
            readSerialCommands.rcvCmdBuffer.append(recVal)
            readSerialCommands.crc ^= recVal
            if len(readSerialCommands.rcvCmdBuffer) >= (fsciDataLengthPos + fsciDataLengthLen):
                readSerialCommands.rcvCmdState = "rcvStateWaitingForData"
                readSerialCommands.dataBytesToReceive = int.from_bytes(readSerialCommands.rcvCmdBuffer[fsciDataLengthPos : fsciDataLengthPos + fsciDataLengthLen],
                                                                       byteorder='little', signed=False);
                readSerialCommands.rcvCmdState = "rcvStateWaitingForData"
        elif readSerialCommands.rcvCmdState == "rcvStateWaitingForData":
            readSerialCommands.rcvCmdBuffer.append(recVal)
            readSerialCommands.crc ^= recVal
            readSerialCommands.dataBytesToReceive -= 1
            if readSerialCommands.dataBytesToReceive == 0:
                readSerialCommands.rcvCmdState = "rcvStateWaitingForCRC"
        elif readSerialCommands.rcvCmdState == "rcvStateWaitingForCRC":
            readSerialCommands.rcvCmdBuffer.append(recVal)
            if recVal != readSerialCommands.crc:
                receivedValidCommand = False
                print ("Warning: Received command with invalid CRC. Expected:",
                       format(readSerialCommands.crc, '#04X'),
                       ", received:",
                       format(recVal, '#04X'),
                       "Ignoring command.")
                print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
            else:
                receivedValidCommand = True
            readSerialCommands.rcvCmdState = "rcvStateWaitingForSync"
        else:
            readSerialCommands.rcvCmdState == "rcvStateWaitingForSync"
            if recVal == fsciSync:
                # the sync has been received, reinitialize the received cmd array
                readSerialCommands.rcvCmdBuffer = array.array('B', recVal.to_bytes(fsciSyncLen, byteorder='little'))
                readSerialCommands.crc = fsciSync;
                readSerialCommands.rcvCmdState = "rcvStateWaitingForOG"
            else:
                #framing error, or serial error, reset the received cmd array
                readSerialCommands.crc = 0;
                readSerialCommands.rcvCmdBuffer = array.array('B')
        
        # print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer],
                # readSerialCommands.dataBytesToReceive,
                # format(readSerialCommands.crc, '#04x'),
                # receivedValidCommand,
                # readSerialCommands.rcvCmdState);
        
        if receivedValidCommand == True:
            retCmdDict["rawCmd"] = readSerialCommands.rcvCmdBuffer;
            
            # If a valid command is received then try to parse it and if it is recognized then return a dictionary with it's parameters
            # Check the command opgroup, if it is not recognized ignore the command and return None immediately
            if readSerialCommands.rcvCmdBuffer[fsciOpGroupPos] != gFsciBleOtapOpcodeGroup_c:
                print ("Warning: Received command with unknown Op Group:", format(readSerialCommands.rcvCmdBuffer[fsciOpGroupPos], '#04X') , "Ignoring Command")
                print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                return None
            
            cmdOpcode = readSerialCommands.rcvCmdBuffer[fsciOpcodePos]
            if   cmdOpcode == gOtapCmdIdNewImageInfoRequest_c:
                if len(readSerialCommands.rcvCmdBuffer) != gFsciOtapCmdIdNewImageInfoRequestLength:
                    print ("Warning: Received command:", cmdOpcode, "with unexpected length :", len(readSerialCommands.rcvCmdBuffer) , "Ignoring Command")
                    print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                    return None
                # The length is valid, extract the parameters
                retCmdDict["cmdType"] = "cmdNewImageInfoRequest";
                currentPos = fsciDataPos;
                retCmdDict["params"]["imageId"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ImageIdFieldSize_c],
                                                                 byteorder='little', signed=False);
                currentPos += gOtap_ImageIdFieldSize_c;
                retCmdDict["params"]["imageVersion"] = format(int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ImageVersionFieldSize_c],
                                                                             byteorder='little', signed=False),
                                                              '#010X');
                return retCmdDict
                
            elif cmdOpcode == gOtapCmdIdImageBlockRequest_c:
                if len(readSerialCommands.rcvCmdBuffer) != gFsciOtapCmdIdImageBlockRequestLength:
                    print ("Warning: Received command:", cmdOpcode, "with unexpected length :", len(readSerialCommands.rcvCmdBuffer) , "Ignoring Command")
                    print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                    return None
                # The length is valid, extract the parameters
                retCmdDict["cmdType"] = "cmdImageBlockRequest";
                currentPos = fsciDataPos;
                retCmdDict["params"]["imageId"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ImageIdFieldSize_c],
                                                                 byteorder='little', signed=False);
                currentPos += gOtap_ImageIdFieldSize_c;
                retCmdDict["params"]["startPosition"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_StartPositionFieldSize_c],
                                                                       byteorder='little', signed=False);
                currentPos += gOtap_StartPositionFieldSize_c;
                retCmdDict["params"]["blockSize"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_BlockSizeFieldSize_c],
                                                                       byteorder='little', signed=False); 
                currentPos += gOtap_BlockSizeFieldSize_c;
                retCmdDict["params"]["chunkSize"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ChunkSizeFieldSize_c],
                                                                       byteorder='little', signed=False); 
                currentPos += gOtap_ChunkSizeFieldSize_c;
                retCmdDict["params"]["transferMethod"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_TransferMethodFieldSize_c],
                                                                       byteorder='little', signed=False); 
                currentPos += gOtap_TransferMethodFieldSize_c;
                retCmdDict["params"]["l2capChannelOrPsm"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_L2capChannelOrPsmFieldSize_c],
                                                                       byteorder='little', signed=False); 
                return retCmdDict
                
            elif cmdOpcode == gOtapCmdIdImageTransferComplete_c:
                if len(readSerialCommands.rcvCmdBuffer) != gFsciOtapCmdIdImageTransferCompleteLength:
                    print ("Warning: Received command:", cmdOpcode, "with unexpected length :", len(readSerialCommands.rcvCmdBuffer) , "Ignoring Command")
                    print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                    return None
                # The length is valid, extract the parameters
                retCmdDict["cmdType"] = "cmdImageTransferComplete";
                currentPos = fsciDataPos;
                retCmdDict["params"]["imageId"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ImageIdFieldSize_c],
                                                                 byteorder='little', signed=False);
                currentPos += gOtap_ImageIdFieldSize_c;
                retCmdDict["params"]["status"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_StatusFieldSize_c],
                                                                 byteorder='little', signed=False);
                return retCmdDict
                
            elif cmdOpcode == gOtapCmdIdErrorNotification_c:
                if len(readSerialCommands.rcvCmdBuffer) != gFsciOtapCmdIdErrorNotificationLength:
                    print ("Warning: Received command:", cmdOpcode, "with unexpected length :", len(readSerialCommands.rcvCmdBuffer) , "Ignoring Command")
                    print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                    return None
                # The length is valid, extract the parameters
                retCmdDict["cmdType"] = "cmdErrorNotification";
                currentPos = fsciDataPos;
                retCmdDict["params"]["cmdId"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_CmdIdFieldSize_c],
                                                               byteorder='little', signed=False);
                currentPos += gOtap_CmdIdFieldSize_c;
                retCmdDict["params"]["errStatus"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_StatusFieldSize_c],
                                                                   byteorder='little', signed=False);
                return retCmdDict
                
            elif cmdOpcode == gOtapCmdIdStopImageTransfer_c:
                if len(readSerialCommands.rcvCmdBuffer) != gFsciOtapCmdIdStopImageTransferLength:
                    print ("Warning: Received command:", cmdOpcode, "with unexpected length :", len(readSerialCommands.rcvCmdBuffer) , "Ignoring Command")
                    print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                    return None
                # The length is valid, extract the parameters
                retCmdDict["cmdType"] = "cmdStopImageTransfer";
                currentPos = fsciDataPos;
                retCmdDict["params"]["imageId"] = int.from_bytes(readSerialCommands.rcvCmdBuffer[currentPos : currentPos + gOtap_ImageIdFieldSize_c],
                                                                 byteorder='little', signed=False);
                return retCmdDict
                
            else:
                print ("Warning: Received command with unknown Op Code:", format(readSerialCommands.rcvCmdBuffer[fsciOpcodePos], '#04X') , "Ignoring Command")
                print ([format(item, '#04X') for item in readSerialCommands.rcvCmdBuffer])
                return None
    
    return None
    # recVal = ord(srvSerial.read())
    # print (str(chr(recVal)), recVal, hex(recVal))
    # write_arr = array.array('B','test\x0D'.encode())
    # written = srvSerial.write(write_arr);
    # if recVal == 255:
        # return readSerialCommands.retCmdDict
    

# ================================================================================================================================================
# ================================================================================================================================================
def getSerialConfiguration ():
    """ This function configures and outputs the serial interface parameters (port and baudrate).
    First it tries to get them from a preconfigured file and if it does not find it it lists
    available serial ports and ports the user to choose one and set a baudrate. 
    Finally it writes the selected configuration to a serial configuration file which will be
    directly used on the next run without prompting for user input.
    The generated file is in human readable .jon format and can be modified by the user to change
    the serial port and the baudrate without running this script again.
    """
    
    serialConfiguration = {"port":         'COM1',
                           "baudrate":     115200 # can be 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200
                          };
            
    
    print("Trying to open default serial configuration file:", serialConfigFileName, "...");
    try:
        serialConfigFile = open(serialConfigFileName, 'r')
        serialConfigFileFound = True;
    except Exception as e:
        serialConfigFileFound = False;
    
    if serialConfigFileFound == True:
        print("Serial configuration file found, trying to load serial configuration...");
        try:
            serialConfig = json.load(serialConfigFile)
        except Exception as e:
            print("Error: Error loading data from serial configuration file ", serialConfigFile, ". Please correct it or delete it and try again.", sep='');
            sys.exit(1);
            
        if "port" not in serialConfig.keys():
            print("Error: The serial configuration file does not contain the expected information:", "port", "Please correct it or delete it and try again.");
            sys.exit(1);    
        if "baudrate" not in serialConfig.keys():
            print("Error: The serial configuration file does not contain the expected information:", "baudrate", "Please correct it or delete it and try again.");
            sys.exit(1);
        print ("Serial configuration successfully loaded from serial configuration file...");
        return serialConfig
    else:
        print("Serial configuration file not found, creating serial configuration. ");
        print("List of available ports (which can be opened):");
        portList = serial_ports()
        print (portList)
        if len(portList) == 0:
            portName = "COM1"
            print ("No ports available, port set to default:", portName)
        else:
            print("Please input the port and press ENTER or press ENTER to use the first in the list:");
            portName = ''
            inputStr = input(">>")
            portName = inputStr;
            while portName not in portList:
                if portName == '':
                    portName = portList[0]
                    print("No port specified, port set to first in the list:", portName);
                    break
                    
                print("Port not in the list, please input the port and press ENTER or press ENTER to use the first in the list:")
                inputStr = input(">>")
                portName = inputStr;
                
        print("Serial port set to:", portName);
        serialConfig = {};
        serialConfig["port"] = portName;
        
        print('Please input the baudrate and press ENTER or press ENTER to use the default (115200) preferably from the standard baudrates \
              (50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 4800, 9600, 19200, 38400, 57600, 115200) \
              although other values may work (0 not allowed):');
        portBaudrate = 0;
        while portBaudrate == 0:
            inputStr = input(">>")
            if inputStr == '':
                portBaudrate = 115200;
            else:
                try:
                    portBaudrate = int(inputStr)
                except Exception as e:
                    portBaudrate = 0;
                if portBaudrate == 0:
                    print("Invalid baudrate input, please try again:");
        print("Serial port baudrate set to:", portBaudrate);
        serialConfig["baudrate"] = portBaudrate;
        
        print ("Creating serial configuration file and writing configuration for later use...");
        
        serialConfig["_comment"]  = "Configure the port and baudrate for the OTAP Server to run on. The default settings are (8 N 1)."
        
        print("Opening output serial configuration file for writing:", serialConfigFileName, "...");
        try:
            serialConfigFile = open(serialConfigFileName, 'w+')
        except Exception as e:
            print("Error: Could not open output serial configuration file ", serialConfigFileName, sep='');
            sys.exit(1);
        
        print("Saving serial configuration data to default file:", serialConfigFileName, "...");
        try:
            json.dump(serialConfig, serialConfigFile, indent=4);
        except Exception as e:
            print("Error: Could not write data to serial configuration file ", serialConfigFileName, sep='');
            sys.exit(1)
            
        serialConfigFile.close()
        return serialConfig
        pass

# ================================================================================================================================================
# ================================================================================================================================================       
def serial_ports():
    """Lists serial ports

    :raises EnvironmentError:
        On unsupported or unknown platforms
    :returns:
        A list of available serial ports
    """
    if sys.platform.startswith('win'):
        ports = ['COM' + str(i + 1) for i in range(256)]

    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this is to exclude your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')

    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')

    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result   
# ================================================================================================================================================
# ================================================================================================================================================
def crcInitial (c):
    """ Precomputed CRC initialization function for 1 byte values. """
    polynomial = 0x1021;
    crc = 0
    c = c << 8
    for j in range(8):
        if (crc ^ c) & 0x8000:
            crc = (crc << 1) ^ polynomial
        else:
            crc = crc << 1
        c = c << 1
    return crc
    
def crcUpdate (crc, c, table):
    """ Updates a CRC with a new 1 byte value and using a given precomputed 0 to 255 table. """
    cc = 0xff & c

    tmp = (crc >> 8) ^ cc
    crc = (crc << 8) ^ table[tmp & 0xff]
    crc = crc & 0xffff
    
    return crc
    
def crcCompute (data, oldCrcValue):
    """ Computes the CRC of an array of 1 byte values starting from a given initial CRC value. """
    crc = oldCrcValue
    # Create a precomputed CRC table for all values from 0 to 255
    crcTable = [ crcInitial(i) for i in range(256) ]
    
    for c in data:
        crc = crcUpdate(crc, c, crcTable)
    return crc

# ================================================================================================================================================
# ================================================================================================================================================
def buildImgFileCrcSubElement (imgCfgDict):
    """ This function parses an executable image file, builds an image sector bitmap sub-element
    and returns meta information about this sub-element.
    """
    retImgFileCrcDict = {"imgFileCrcSubElemBuildSuccess":   True,
                         "binaryImgFileCrcSubElem":         array.array('B'),
                         "imgFileCrcSubElemWrittenLen":     0};
    
    # Check if the provided input data contains the necessary information to build the image file CRC sub-element
    if "sectorBitmap" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain image file CRC information.");
        retImgFileCrcDict["imgFileCrcSubElemBuildSuccess"] = False;
        return retImgFileCrcDict;
    if "imageFileCrcSize" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain image file CRC size information.");
        retImgFileCrcDict["imgFileCrcSubElemBuildSuccess"] = False;
        return retImgFileCrcDict;
    if imgCfgDict["imageFileCrcSize"] == 0:
        print("Error: The image configuration file image file CRC size is invalid.");
        retImgFileCrcDict["imgFileCrcSubElemBuildSuccess"] = False;
        return retImgFileCrcDict;
        
    # Create the sub-element header
    retImgFileCrcDict["binaryImgFileCrcSubElem"].extend(array.array('B',imageFileCrcSubElementType.to_bytes(subElementTypeSize, byteorder='little')));
    retImgFileCrcDict["binaryImgFileCrcSubElem"].extend(array.array('B',imgCfgDict["imageFileCrcSize"].to_bytes(subElementLengthSize, byteorder='little')));
    
    retImgFileCrcDict["binaryImgFileCrcSubElem"].extend(array.array('B', [0] * imgCfgDict["imageFileCrcSize"]));
    retImgFileCrcDict["imgFileCrcSubElemWrittenLen"] = len(retImgFileCrcDict["binaryImgFileCrcSubElem"]);
    return retImgFileCrcDict;

# ================================================================================================================================================
# ================================================================================================================================================
def buildImgSectorBitmapSubElement (imgCfgDict):
    """ This function parses an executable image file, builds an image sector bitmap sub-element
    and returns meta information about this sub-element.
    """
    retImgSectBitmapDict = {"imgSectBitmapSubElemBuildSuccess": True,
                            "binaryImgSectBitmapSubElem":       array.array('B'),
                            "imgSectBitmapSubElemWrittenLen":   0};

    # Check if the provided input data contains the necessary information to build the image sector bitmap sub-element
    if "sectorBitmap" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain image sector bitmap information.");
        retImgSectBitmapDict["imgSectBitmapSubElemBuildSuccess"] = False;
        return retImgSectBitmapDict;
    if "sectorBitmapSize" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain image sector bitmap size information.");
        retImgSectBitmapDict["imgSectBitmapSubElemBuildSuccess"] = False;
        return retImgSectBitmapDict;
    if len(imgCfgDict["sectorBitmap"]) != (imgCfgDict["sectorBitmapSize"] * 2):
        print("Error: The image configuration file image sector bitmap does not have the declared length.");
        retImgSectBitmapDict["imgSectBitmapSubElemBuildSuccess"] = False;
        return retImgSectBitmapDict;
    
    # Create the sub-element header
    retImgSectBitmapDict["binaryImgSectBitmapSubElem"].extend(array.array('B',imageSectorBitmapSubElementType.to_bytes(subElementTypeSize, byteorder='little')));
    retImgSectBitmapDict["binaryImgSectBitmapSubElem"].extend(array.array('B',imgCfgDict["sectorBitmapSize"].to_bytes(subElementLengthSize, byteorder='little')));
    
    retImgSectBitmapDict["binaryImgSectBitmapSubElem"].extend(array.array('B', bytes.fromhex(imgCfgDict["sectorBitmap"])));
    retImgSectBitmapDict["imgSectBitmapSubElemWrittenLen"] = len(retImgSectBitmapDict["binaryImgSectBitmapSubElem"]);
    return retImgSectBitmapDict;
                        
# ================================================================================================================================================
# ================================================================================================================================================
def buildImageSubElement(exImgFile):
    """ This function parses an executable image file, builds an image sub-element
    and returns meta information about this sub-element.
    """
    retImgSubElemDict = {"imgSubElemBuildSuccess":  True,
                         "binaryImgSubElem":        array.array('B'),
                         "imgSubElemWrittenLen":    0};
                         
    imgSubElemBinaryPos = 0;
    
    recordTypeSize = 2; #in ASCII hex characters
    byteCountSize = 2; #in ASCII hex characters
    checksumSize = 2; #in ASCII hex characters
    terminatorSize = 1; #in ASCII hex characters

    # Create the sub-element header
    retImgSubElemDict["binaryImgSubElem"].extend(array.array('B',imageSubElementType.to_bytes(subElementTypeSize, byteorder='little')));
    imgSubElemBinaryPos += subElementTypeSize;
    retImgSubElemDict["binaryImgSubElem"].extend(array.array('B',[0] * subElementLengthSize));
    imgSubElemBinaryPos += subElementLengthSize;
    for li, line in enumerate(exImgFile, start=1):
        byteCount = 0; #in bytes
        dataSize = 0; #in bytes
        addressSize = 0; #in ASCII hex characters
        if (li == 1):
            if(line[0:recordTypeSize] != 'S0'):
                print("Error: Invalid executable image file format on line:", li);
                retImgSubElemDict["imgSubElemBuildSuccess"] = False;
                return retImgSubElemDict;

        if   (line[0:recordTypeSize] == 'S0'):
            #ignore this type of record
            pass
        elif (line[0:recordTypeSize] == 'S1'):
            addressSize = 4;
        elif (line[0:recordTypeSize] == 'S2'):
            addressSize = 6;
        elif (line[0:recordTypeSize] == 'S3'):
            addressSize = 8;
        elif (line[0:recordTypeSize] == 'S4') or \
             (line[0:recordTypeSize] == 'S5') or \
             (line[0:recordTypeSize] == 'S6') or \
             (line[0:recordTypeSize] == 'S7') or \
             (line[0:recordTypeSize] == 'S8') or \
             (line[0:recordTypeSize] == 'S9'):
            #ignore this type of record
            pass
        else:
            print("Error: Invalid executable image file format on line:", li);
            retImgSubElemDict["imgSubElemBuildSuccess"] = False;
            return retImgSubElemDict;

        #if the addressSize variable is set this line must be parsed
        if addressSize != 0:
            try:
                byteCount = int(line[recordTypeSize:recordTypeSize + byteCountSize], 16);
            except Exception as e:
                print("Error: Invalid executable image file format on line:", li);
                retImgSubElemDict["imgSubElemBuildSuccess"] = False;
                return retImgSubElemDict;
            if (len(line) != 2 * byteCount + recordTypeSize + byteCountSize + terminatorSize):
                print("Error: Invalid line length on line:", li);
                retImgSubElemDict["imgSubElemBuildSuccess"] = False;
                return retImgSubElemDict;
            dataSize = byteCount - checksumSize/2 - addressSize/2; # these are bytes, divide by two
            address = 0;
            for ai in range(0, addressSize, 2):
                address = address << 8;
                address += int(line[recordTypeSize+byteCountSize + ai:recordTypeSize+byteCountSize + ai + 2], 16)
                #print('r',ai)
            # address = (int(line[recordTypeSize+byteCountSize:recordTypeSize+byteCountSize+2], 16) << 8) + \
            #           (int(line[recordTypeSize+byteCountSize+2:recordTypeSize+byteCountSize+4], 16));
            currentDataBinaryPosition = imgSubElemBinaryPos - subElementTypeSize - subElementLengthSize;
            if currentDataBinaryPosition < address:
                retImgSubElemDict["binaryImgSubElem"].extend(array.array('B',[0xFF]*(address - currentDataBinaryPosition)));
                imgSubElemBinaryPos = address + subElementTypeSize + subElementLengthSize;
            lineChecksum = int(line[-terminatorSize-checksumSize:-terminatorSize], 16);
            computedChecksum = byteCount;
            for ci in range(recordTypeSize + byteCountSize, len(line) - terminatorSize - checksumSize, 2): # -1 for string terminator, -2 for actual checksum
                currentByte = int(line[ci:ci+2], 16);
                computedChecksum += currentByte;
                if ci >= recordTypeSize + byteCountSize + addressSize:
                    retImgSubElemDict["binaryImgSubElem"].extend(array.array('B',currentByte.to_bytes(1, byteorder='little')));
                    imgSubElemBinaryPos += 1;
            computedChecksum = (~computedChecksum & 0xFF);
            if (computedChecksum != lineChecksum):
                print("Error: Invalid line checksum on line:", li);
                retImgSubElemDict["imgSubElemBuildSuccess"] = False;
                return retImgSubElemDict;
            # if li >= 175 and li <=185:
               # print (li, address, dataSize, imgSubElemBinaryPos - subElementTypeSize - subElementLengthSize, format(lineChecksum, '#04x'), format(computedChecksum, '#04x'))

        # if (li == 2):
            # pass
            #break
            
    # Insert binary image length into binary image sub element header
    insertIntValueIntoBinaryArray (retImgSubElemDict["binaryImgSubElem"],
                                   imgSubElemBinaryPos - subElementTypeSize - subElementLengthSize,
                                   subElementTypeSize,
                                   subElementLengthSize);
        
    retImgSubElemDict["imgSubElemWrittenLen"] = imgSubElemBinaryPos;
    return retImgSubElemDict;

# ================================================================================================================================================
# ================================================================================================================================================
def insertIntValueIntoBinaryArray(binArray, value, arrayValPos, arrayValLen):
    """ This function will insert a guven value into an array at the specified position
    and it will truncate the value to the specified length in little endian format.
    """
    binArray[arrayValPos : arrayValPos + arrayValLen] = array.array('B', value.to_bytes(arrayValLen, byteorder='little'));

# ================================================================================================================================================
# ================================================================================================================================================
def buildImgFileHeader (imgCfgDict):
    """ This function parses an image file configuration data structure obtained from an
    an image file configuration file, builds the image file header and returns the positions
    and sizes of some header elements which must be later filled.
    """
    returnHeaderDict = {"hdrBuildSuccess":  True,
                        "binaryHeader":     array.array('B'),
                        "imgFileVersion":   '',   
                        "writtenLen": 0,
                        "imgFileSizePos":   0,
                        "imgFileSizeLen":   0,
                        "imgIdPos":         0,
                        "imgIdLen":         0};

    if "header" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain header information.");
        returnHeaderDict["hdrBuildSuccess"] = False;
        return returnHeaderDict;
    if "headerSize" not in imgCfgDict.keys():
        print("Error: The image configuration file does not contain header size information.");
        returnHeaderDict["hdrBuildSuccess"] = False;
        return returnHeaderDict;
    if len(imgCfgDict["header"]) == 0:
        print("Error: The image configuration file header does not contain enough elements.");
        returnHeaderDict["hdrBuildSuccess"] = False;
        return returnHeaderDict;

    headerIndex = 1;
    headerBinaryIndex = 0;
    while headerIndex <= len (imgCfgDict["header"]):
        headerIndexFound = False;
        for elem in imgCfgDict["header"]:
            if ("index" not in elem) or ("name" not in elem) or ("size" not in elem) or ("value" not in elem):
                print("Error: The image configuration file header has incomplete elements.");
                returnHeaderDict["hdrBuildSuccess"] = False;
                return returnHeaderDict;
            if elem["index"] == headerIndex:
                headerIndexFound = True;
                if elem["size"] + headerBinaryIndex > imgCfgDict["headerSize"]:
                    print("Error: The image configuration file header elements total size is larger than the declared header size.");
                    returnHeaderDict["hdrBuildSuccess"] = False;
                    return returnHeaderDict;
                if   (elem["name"] == "fileIdentifier"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "headerVersion"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "headerLength"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 10).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "fieldControl"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "companyId"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "imageId"):
                    returnHeaderDict["imgIdPos"] = headerBinaryIndex;
                    returnHeaderDict["imgIdLen"] = elem["size"];
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                        returnHeaderDict["imageId"] = int(elem["value"], 16)
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "imageVersion"):
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    returnHeaderDict["imgFileVersion"] = elem["value"];
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "headerString"):
                    try:
                        if len(elem["value"]) < elem["size"]:
                            returnHeaderDict["binaryHeader"].extend(array.array('B',bytearray(elem["value"][0:len(elem["value"])+1], encoding='utf-8')));
                            returnHeaderDict["binaryHeader"].extend(array.array('B',[0]*(elem["size"] - len(elem["value"]))));
                        else:
                            returnHeaderDict["binaryHeader"].extend(array.array('B',bytearray(elem["value"][0:elem["size"]+1], encoding='utf-8')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                elif (elem["name"] == "totalImageFileSize"):
                    returnHeaderDict["imgFileSizePos"] = headerBinaryIndex;
                    returnHeaderDict["imgFileSizeLen"] = elem["size"];
                    try:
                        returnHeaderDict["binaryHeader"].extend(array.array('B',int(elem["value"], 16).to_bytes(elem["size"], byteorder='little')));
                    except Exception as e:
                        print("Error: The image header element >>", elem["name"], "<< has an incorrectly formatted value.", sep='');
                        returnHeaderDict["hdrBuildSuccess"] = False;
                        return returnHeaderDict;
                    headerBinaryIndex += elem["size"];
                else:
                    returnHeaderDict["binaryHeader"].extend(array.array('B',[0]*elem["size"]));
                    headerBinaryIndex += elem["size"];
                    pass

        if headerIndexFound == False:
            print("Error: The image configuration file header has miss-indexed elements.");
            returnHeaderDict["hdrBuildSuccess"] = False;
            return returnHeaderDict;
        headerIndex += 1;

    if headerBinaryIndex != imgCfgDict["headerSize"]:
        print("Error: The image header elements total size does not equal the declared header size.");
        returnHeaderDict["hdrBuildSuccess"] = False;
        return returnHeaderDict;
    else:
        returnHeaderDict["writtenLen"] = headerBinaryIndex;

    return returnHeaderDict;

if __name__ == "__main__":
    otaps(sys.argv[1:])
