
/** BLE SIG SERVICES */

PRIMARY_SERVICE(service_gatt, gBleSig_GenericAttributeProfile_d)
        CHARACTERISTIC(char_service_changed, gBleSig_GattServiceChanged_d, (gGattCharPropRead_c | gGattCharPropNotify_c) )
            VALUE(value_service_changed, gBleSig_GattServiceChanged_d, (gPermissionNone_c), 4, 0x00, 0x00, 0x00, 0x00)
            CCCD(cccd_service_changed)

PRIMARY_SERVICE(service_gap, gBleSig_GenericAccessProfile_d)
    CHARACTERISTIC(char_device_name, gBleSig_GapDeviceName_d, (gGattCharPropRead_c) )
            VALUE(value_device_name, gBleSig_GapDeviceName_d, (gPermissionFlagReadable_c), 8, "HEXIWEAR")
                
    CHARACTERISTIC(char_appearance, gBleSig_GapAppearance_d, (gGattCharPropRead_c) )
            VALUE(value_appearance, gBleSig_GapAppearance_d, (gPermissionFlagReadable_c), 2, 0x80, 0x03)
                
    CHARACTERISTIC(char_ppcp, gBleSig_GapPpcp_d, (gGattCharPropRead_c) )
            VALUE(value_ppcp, gBleSig_GapPpcp_d, (gPermissionFlagReadable_c), 8, 0x30, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x0C)

PRIMARY_SERVICE_UUID128(service_otap, uuid_service_otap)
    CHARACTERISTIC_UUID128(char_otap_control_point, uuid_char_otap_control_point, (gGattCharPropWrite_c | gGattCharPropIndicate_c))
        VALUE_UUID128_VARLEN(value_otap_control_point, uuid_char_otap_control_point, (gPermissionFlagWritable_c), 16, 16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
        CCCD(cccd_otap_control_point)
    CHARACTERISTIC_UUID128(char_otap_data, uuid_char_otap_data, (gGattCharPropWriteWithoutRsp_c))
        VALUE_UUID128_VARLEN(value_otap_data, uuid_char_otap_data, (gPermissionFlagWritable_c), 20, 20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)                
    CHARACTERISTIC_UUID128(char_otap_state, uuid_char_otap_state, (gGattCharPropRead_c))
        VALUE_UUID128(value_otap_state, uuid_char_otap_state, (gPermissionFlagReadable_c), 1, 0x00)                        
        
PRIMARY_SERVICE(service_device_info, gBleSig_DeviceInformationService_d)
    CHARACTERISTIC(char_manuf_name, gBleSig_ManufacturerNameString_d, (gGattCharPropRead_c) )
        VALUE(value_manuf_name, gBleSig_ManufacturerNameString_d, (gPermissionFlagReadable_c), 16, "Mikroelektronika")
    CHARACTERISTIC(char_fw_rev, gBleSig_FirmwareRevisionString_d, (gGattCharPropRead_c) )
        VALUE(value_fw_rev, gBleSig_FirmwareRevisionString_d, (gPermissionFlagReadable_c), 11, "")
    CHARACTERISTIC(char_serial_num, gBleSig_SerialNumberString_d, (gGattCharPropRead_c) )
        VALUE(value_serial_num, gBleSig_SerialNumberString_d, (gPermissionFlagReadable_c), 10, "serial num")
            
            
            
PRIMARY_SERVICE(service_battery, gBleSig_BatteryService_d)
    CHARACTERISTIC(char_battery_level, gBleSig_BatteryLevel_d, (gGattCharPropNotify_c | gGattCharPropRead_c))
        VALUE(value_battery_level, gBleSig_BatteryLevel_d, (gPermissionFlagReadable_c), 1, 0x5A)
        DESCRIPTOR(desc_bat_level, gBleSig_CharPresFormatDescriptor_d, (gPermissionFlagReadable_c), 7, 0x04, 0x00, 0xAD, 0x27, 0x01, 0x01, 0x00)
        CCCD(cccd_battery_level)
            
/** BLE CUSTOM SERVICES */
                      
PRIMARY_SERVICE(service_motion, gBleCustom_MotionService_d)
    CHARACTERISTIC(char_accel, gBleCustom_AccelUUID_d, gGattCharPropRead_c)
        VALUE(value_accel, gBleCustom_AccelUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_AccelLength_d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
//        DESCRIPTOR(desc_accel, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 5, "Accel")       
            
    CHARACTERISTIC(char_gyro, gBleCustom_GyroUUID_d, gGattCharPropRead_c)
        VALUE(value_gyro, gBleCustom_GyroUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_GyroLength_d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
//        DESCRIPTOR(desc_gyro, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 5, "Gyro")       
            
    CHARACTERISTIC(char_magnet, gBleCustom_MagnetUUID_d, gGattCharPropRead_c)
        VALUE(value_magnet, gBleCustom_MagnetUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_MagnetLength_d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)
//        DESCRIPTOR(desc_magnet, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 6, "Magnet")       
            
            
            
PRIMARY_SERVICE(service_weather, gBleCustom_WeatherService_d)
    CHARACTERISTIC(char_ambiLight, gBleCustom_AmbiLightUUID_d, gGattCharPropRead_c)
        VALUE(value_ambiLight, gBleCustom_AmbiLightUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_AmbiLightLength_d, 0x00)
//        DESCRIPTOR(desc_ambiLight, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 12, "AmbientLight")
           
    CHARACTERISTIC(char_temperature, gBleCustom_TemperatureUUID_d, gGattCharPropRead_c)
        VALUE(value_temperature, gBleCustom_TemperatureUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_TemperatureLength_d, 0x00, 0x00)
//        DESCRIPTOR(desc_temperature, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 11, "Temperature")

    CHARACTERISTIC(char_humidity, gBleCustom_HumidityUUID_d, gGattCharPropRead_c)
        VALUE(value_humidity, gBleCustom_HumidityUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_HumidityLength_d, 0x00, 0x00)
//        DESCRIPTOR(desc_humidity, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 8, "Humidity")
            
    CHARACTERISTIC(char_pressure, gBleCustom_PressureUUID_d, gGattCharPropRead_c)
        VALUE(value_pressure, gBleCustom_PressureUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_PressureLength_d, 0x00, 0x00)
//        DESCRIPTOR(desc_pressure, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 8, "Pressure")
            
            
            
PRIMARY_SERVICE(service_health, gBleCustom_HealthService_d)
    CHARACTERISTIC(char_heartRate, gBleCustom_HeartRateUUID_d, gGattCharPropRead_c)
        VALUE(value_heartRate, gBleCustom_HeartRateUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_HeartRateLength_d, 0x00)
//        DESCRIPTOR(desc_heartRate, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 9, "HeartRate")
           
    CHARACTERISTIC(char_steps, gBleCustom_StepsUUID_d, gGattCharPropRead_c)
        VALUE(value_steps, gBleCustom_StepsUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_StepsLength_d, 0x00)
//        DESCRIPTOR(desc_steps, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 5, "Steps")

    CHARACTERISTIC(char_calorie, gBleCustom_CalorieUUID_d, gGattCharPropRead_c)
        VALUE(value_calorie, gBleCustom_CalorieUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_CalorieLength_d, 0x00, 0x00)
//        DESCRIPTOR(desc_activityTime, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 12, "ActivityTime")

            
                       
PRIMARY_SERVICE(service_alert, gBleCustom_AlertService_d)
    CHARACTERISTIC(char_alertIn, gBleCustom_AlertInUUID_d, (gGattCharPropWrite_c | gGattCharPropRead_c))
        VALUE(value_alertIn, gBleCustom_AlertInUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c | gPermissionFlagWritable_c | gPermissionFlagWriteWithAuthentication_c), gBleCustom_AlertInLength_d, 0x00, 0x00, 0x00)
//        DESCRIPTOR(desc_alertIn, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 7, "AlertIn")
            
    CHARACTERISTIC(char_alertOut, gBleCustom_AlertOutUUID_d, (gGattCharPropNotify_c | gGattCharPropRead_c))
        VALUE(value_alertOut, gBleCustom_AlertOutUUID_d, (gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c), gBleCustom_AlertOutLength_d, 0x00, 0x00, 0x00)
//        DESCRIPTOR(desc_alertOut, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 8, "AlertOut")
        CCCD(cccd_alertOut)
            
            
            
PRIMARY_SERVICE(service_appMode, gBleCustom_AppModeService_d)
    CHARACTERISTIC(char_appMode, gBleCustom_AppModeUUID_d, (gGattCharPropNotify_c | gGattCharPropRead_c))
        VALUE(value_appMode, gBleCustom_AppModeUUID_d, gPermissionFlagReadable_c | gPermissionFlagReadWithAuthentication_c, gBleCustom_AppModeLength_d, 0x00)
//        DESCRIPTOR(desc_appMode, gBleSig_CharUserDescriptor_d, (gPermissionFlagReadable_c), 8, "App Mode")
        CCCD(cccd_appMode)
            
            