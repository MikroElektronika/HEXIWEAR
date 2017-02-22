-------------------
Current NFC support
-------------------
NFC is started at boot (case where NFC Click is not present been handled properly).
A new NFC sub-menu inside "Settings" menu allow enabling/disabling NFC and reflect NFC state (similar to bluetooth).
Currently implemented use cases so far are:
- automatic launch of Hexiwear android application when a NFC enabled smartphone is tapped
- automatic launch of Pedometer or HearRate monitor application on Hexiwear when the related "Application launch" card is tapped
- handling of Relays states thanks to the related "Relay control" cards

------------------
Current limitation
------------------
- "Sensor Tag" cannot be enabled (enabling it from the menu trigger Hexiwear reboot)
- Missing an easy way to save/restore the current display context in order to temporary display information related to NFC before coming back to the existing context/application
