
/**
 * [getApp_Init description]
 * @param param [description]
 */
void getApp_Init( void* param )
{
    power_DisablePowerSave();
}
/**
 * [getApp_Destroy description]
 * @param param [description]
 */

void getApp_Destroy( void* param )
{
    power_EnablePowerSave();
}
