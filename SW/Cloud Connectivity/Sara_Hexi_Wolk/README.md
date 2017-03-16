# SARA_3G_Hexiwear_WolkSense Example
  
  In order to successfully build this project, you need to add some additional include directories to the search paths.
  To do this, open the "Search Paths" window by choosing "Project->Edit Search paths..." option from the menu, or by using the shortcut Crtl+Shift+P.
  In the "Search Paths" window click on the "Add header path" button (the first button in the "Header Files" section) and add these three paths (replace the "..." with the project root folder path):
    - ...\RTOS\include\
    - ...\wolksense_conn\include\
    - ...\mqtt\include\

## About
  WiFi_Hexiwear_WolkSense Example demonstrates how to directly connect Hexiwear to the [WolkSense Sensor Data Cloud](https://wolksense.com/). The data read from the Hexiwear is sent to [WolkSense Sensor Data Cloud](https://wolksense.com/), where you can monitor the changes read by the Hexiwear.
  Direct connection to [WolkSense Sensor Data Cloud](https://wolksense.com/) has been has been astablished with "3G Sara click".
  
## Setup of the SARA_3G_Hexiwear_WolkSense Example
  
### Running this example has 2 preconditions:

* "Device registration to [WolkSense Sensor Data Cloud](https://wolksense.com/)" - this is necessary for monitoring the read values from your Hexiwear on [WolkSense Sensor Data Cloud](https://wolksense.com/).
* "Project configuration" - the customization of the project's configuration is necessary, so that the Hexiwear would send it's read values to your [WolkSense Sensor Data Cloud](https://wolksense.com/) account. 
  
### Device registration to [WolkSense Sensor Data Cloud](https://wolksense.com/):

	The python project for device registration can be downloaded from the [WolkConnect-Python](https://github.com/Wolkabout/WolkConnect-Python-) project

	Upon successful execution you should see new devices and new readings on https://wolksense.com and you will receive a serial code and a password. The serial code and the password will be needed in the project configuration

	  Example output of python script:
		
	  Activating ControlDeviceWifi ...
		ControlDeviceWifi activated with serial:0317GD007XHTWCC7 password:jqfnxujpadccykn3
		  

### Project configuration
	 
	1. Place WiFi click on the number 1 slot of  Hexiwear docking station.
	 
	2. After opening  the project with "mikroC PRO for ARM" you will need to edit the Search Paths:
			
	3. Try to compile project so that invalid paths can be identified
	  Open "Search Paths" dialog through the "Project"->"Edit Search Paths..." menu-item or just click "Shift+Ctrl+P"
	  In the "Search Paths" dialog click on the "Purge invalid paths" for the source files and the header files as well
	  Click on the "source files"'s "Add search path" button, find the opened project in the list, select the "Project_name->RTOS->source" folder and click on the OK button 
	  Click on the "header files"'s "Add header path" button, find the opened project in the list, select the "Project_name->RTOS->include" folder and click on the OK button 
	  Close the dialog with "OK"

	4. Set mqtt username and password:
			
	  add your "serial code" and "password" to the projects main.c file's parameters (the "serial code" and "password" were received from the example.py):
		username_mqtt[] = "serial code"
		password_mqtt[] = "password";
		topic[] = "sensors/"serial code"";
	  
    
    5. Set 3G parameters:
  
      For example:  
      const char carrier[] = "Telenor";
      const char username[] = "telenor";
      const char password[] = "gprs";