/* 
* Declare all custom 128-bit UUIDs here using the format:
*
*  UUID128(name, bytes)
*
* where: 
*	-name : an unique tag for the newly defined UUID;
		will be used to reference this UUID when defining
		services and characteristics in <<gattDb.h>>
*	-bytes: 16 bytes representing the 128-bit value
*
* One definition per line. No semicolon required after each definition.
*
* example:
*  UUID128(uuid_service_robot_characteristics, 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF)
*  UUID128(uuid_char_robot_direction, 0x12, 0x34, 0x50, 0x00, 0x90, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF)
*	
*/



/*! Bluetooth Custom UUID constants for GATT declarations (16-bit format for now)*/



/*! Client Extended Properties Descriptor declaration UUID */
#define gBleSig_CharExtendPropDescriptor_d      0x2900
/*! Client User Description Descriptor declaration UUID */
#define gBleSig_CharUserDescriptor_d            0x2901


                    
/*! Accelerometer Magnetometer Gyroscope Service */
#define gBleCustom_MotionService_d              0x2000

#define gBleCustom_AccelUUID_d                  0x2001
#define gBleCustom_AccelLength_d                6

#define gBleCustom_GyroUUID_d                   0x2002
#define gBleCustom_GyroLength_d                 6

#define gBleCustom_MagnetUUID_d                 0x2003
#define gBleCustom_MagnetLength_d               6



/*! Temperature Humidity Pressure Service */
#define gBleCustom_WeatherService_d             0x2010

#define gBleCustom_AmbiLightUUID_d              0x2011
#define gBleCustom_AmbiLightLength_d            1

#define gBleCustom_TemperatureUUID_d            0x2012
#define gBleCustom_TemperatureLength_d          2

#define gBleCustom_HumidityUUID_d               0x2013
#define gBleCustom_HumidityLength_d             2

#define gBleCustom_PressureUUID_d               0x2014
#define gBleCustom_PressureLength_d             2



/*! Health Service */
#define gBleCustom_HealthService_d              0x2020

#define gBleCustom_HeartRateUUID_d              0x2021
#define gBleCustom_HeartRateLength_d            1

#define gBleCustom_StepsUUID_d                  0x2022
#define gBleCustom_StepsLength_d                2

#define gBleCustom_ActivityTimeUUID_d           0x2023
#define gBleCustom_ActivityTimeLength_d         2



/*! Alert/Command Service */
#define gBleCustom_AlertService_d               0x2030

#define gBleCustom_AlertInUUID_d                0x2031
#define gBleCustom_AlertInLength_d              20

#define gBleCustom_AlertOutUUID_d               0x2032
#define gBleCustom_AlertOutLength_d             20

