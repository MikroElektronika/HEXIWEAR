-------------------
Loading KDS project
-------------------
In a new KDS workspace:
1. import ksdk_platform_lib_K64F12 project from KSDK1.3 (without copying the project into the workspace)
2. import HEXIWEAR_Nfc_Click project from the related zip file
3. in HEXIWEAR_Nfc_Click project properties (C/C++ Build - Build Variables) update "PROJECT_KSDK_PATH" variable to reflect the KSDK1.3 installation path
4. build HEXIWEAR_Nfc_Click project (implicitly building ksdk_platform_lib_K64F12 library)
5. flash and debug using included PyOCD debug configuration

-----------------
NFC click example
-----------------
The application starts diplaying HEXIWEAR/NFC logos.
On this screen:
- tapping an Android NFC enabled Smartphone will trigger the HExiwear android Application being started on the phone side (if the app is not yet install it will guide user to the related page on play store).
- tapping a card will, depending of the information contained:
    o "Color cards": change the color of the Hexiwear LED
    o "URL" cards: related URL is been displayed on the screen
    o "Text" cards: related TEXT is been displayed on the screen
    o "Business" cards: relates Full name is displayed on the screen
    o "Access control" cards: display related user name and dedicated logo "GRANTED" or "DENIED"
On the second screen (reached using right or up buttons), a mood logo is being displayed. The mood status is updated each time a "mood" card is tapped (either mood increase or mood decrease).
On the third screen, a bluetooth logo is displayed. Tapping an NFC enabled Smartphone will trigger BT connection (failing because of the current pairing configuration of KW40 requiring pin code).

--------------------------------
Instructions to create NFC cards 
--------------------------------
Easiest way is make use of an Android NFC enabled smartphone and "NFC TagWriter by NXP" application available on google play store.
Then from "My datasets" import the shared dataset file "NFC_click-dataset.twdb" for further tags writing.
Otherwise you can create your own card using "NFC TagWriter by NXP" application, or "NFC Tools" (by wakdev) for cards requiring multiple entries (Access control ones).

- "Color cards": 
    NDEF text record encoded as "RGB:xxyyzz" (xx indicates Red value in hexadecimal, yy Green one and zz Blue one).
    Due to the limited control of the LED, only values 00 or FF are supported.
    Example: "RGB:FF0000" gives "Set LED red" command.

- "URL" cards: 
    NDEF URI record (Link)
    Example: "www.nxp.com"
    
- "Text" cards:
    NDEF text record (Plain text)
    Example: "Hello world !"
    
- "Business" cards: 
    NDEF MIME type record, "text/x-vCard" type (Business card)
    Example: Full name="Gregory Camuzat"

- "Access control" cards: Contain 2 entries
    o NDEF MIME type record, "text/x-vCard" type (Business card)
      Example: Full name="Gregory Camuzat"
    o NDEF text record (Plain text) encoded as "ACCESS GRANTED" or ACCESS DENIED"
      Example: "ACCESS GRANTED"

- "Mood" cards:
    NDEF text record (Plain text) recorded as "MOOD INCREASE" or "MOOD DECREASE"
    Example: "MOOD INCREASE"

- "Application launch" cards:
    NDEF text record (Plain text) recorded as "Pedometer" or "HeartRate"
    Example: "Pedometer"

- "Relay control" cards:
    NDEF text record (Plain text) recorded as "RELx:'action'" (x indicates relay to control, 'action' can be ON, OFF or toggle)
    Example: "REL1:toggle"

