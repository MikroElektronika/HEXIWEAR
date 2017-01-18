REM *******************************************************
REM * Batch file to program a bin file with Segger J-Link *
REM *******************************************************

SET JLINK="C:\Program Files (x86)\SEGGER\JLink_V612\JLink.exe"

%JLINK% -device MK64FN1M0xxx12 -CommanderScript ./jlink_k64f.script
pause
