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

UUID128(uuid_service_ancs,           0xD0, 0x00, 0x2D, 0x12, 0x1E, 0x4B, 0x0F, 0xA4, 0x99, 0x4E, 0xCE, 0xB5, 0x31, 0xF4, 0x05, 0x79)
UUID128(uuid_char_ancs_notif_source, 0xBD, 0x1D, 0xA2, 0x99, 0xE6, 0x25, 0x58, 0x8C, 0xD9, 0x42, 0x01, 0x63, 0x0D, 0x12, 0xBF, 0x9F)
UUID128(uuid_char_ancs_ctrl_point,   0xD9, 0xD9, 0xAA, 0xFD, 0xBD, 0x9B, 0x21, 0x98, 0xA8, 0x49, 0xE1, 0x45, 0xF3, 0xD8, 0xD1, 0x69)
UUID128(uuid_char_ancs_data_source,  0xFB, 0x7B, 0x7C, 0xCE, 0x6A, 0xB3, 0x44, 0xBE, 0xB5, 0x4B, 0xD6, 0x24, 0xE9, 0xC6, 0xEA, 0x22)

UUID128(uuid_service_otap,              0xE0, 0x1C, 0x4B, 0x5E, 0x1E, 0xEB, 0xA1, 0x5C, 0xEE, 0xF4, 0x5E, 0xBA, 0x50, 0x55, 0xFF, 0x01)
UUID128(uuid_char_otap_control_point,   0xE0, 0x1C, 0x4B, 0x5E, 0x1E, 0xEB, 0xA1, 0x5C, 0xEE, 0xF4, 0x5E, 0xBA, 0x51, 0x55, 0xFF, 0x01)
UUID128(uuid_char_otap_data,            0xE0, 0x1C, 0x4B, 0x5E, 0x1E, 0xEB, 0xA1, 0x5C, 0xEE, 0xF4, 0x5E, 0xBA, 0x52, 0x55, 0xFF, 0x01)
UUID128(uuid_char_otap_state,           0xE0, 0x1C, 0x4B, 0x5E, 0x1E, 0xEB, 0xA1, 0x5C, 0xEE, 0xF4, 0x5E, 0xBA, 0x53, 0x55, 0xFF, 0x01)

/*! Client Extended Properties Descriptor declaration UUID */
#define gBleSig_CharExtendPropDescriptor_d      0x2900
/*! Client User Description Descriptor declaration UUID */
#define gBleSig_CharUserDescriptor_d            0x2901

/*! Bluetooth Custom UUID constants for GATT declarations (16-bit format for now)*/
                    
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

#define gBleCustom_CalorieUUID_d                0x2023
#define gBleCustom_CalorieLength_d              2



/*! Alert/Command Service */
#define gBleCustom_AlertService_d               0x2030

#define gBleCustom_AlertInUUID_d                0x2031
#define gBleCustom_AlertInLength_d              20

#define gBleCustom_AlertOutUUID_d               0x2032
#define gBleCustom_AlertOutLength_d             20



/*! Alert/Command Service */
#define gBleCustom_AppModeService_d             0x2040

#define gBleCustom_AppModeUUID_d                0x2041
#define gBleCustom_AppModeLength_d              1

