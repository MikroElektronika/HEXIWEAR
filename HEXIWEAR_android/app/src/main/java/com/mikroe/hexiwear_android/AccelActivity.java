package com.mikroe.hexiwear_android;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.TextView;

import java.util.ArrayList;

public class AccelActivity extends Activity {

    private CustomProgress_Vertical progressBarX;
    private CustomProgress_Vertical progressBarY;
    private CustomProgress_Vertical progressBarZ;

    private HexiwearService hexiwearService;

    private final ArrayList<String> uuidArray = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.accel_screen);

        uuidArray.add(HexiwearService.UUID_CHAR_ACCEL);

        progressBarX = (CustomProgress_Vertical) findViewById(R.id.accelProgressX);
        progressBarY = (CustomProgress_Vertical) findViewById(R.id.accelProgressY);
        progressBarZ = (CustomProgress_Vertical) findViewById(R.id.accelProgressZ);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    @Override

    protected void onResume() {
        super.onResume();

        hexiwearService = new HexiwearService(uuidArray);
        hexiwearService.readCharStart(10);
        registerReceiver(mGattUpdateReceiver, makeGattUpdateIntentFilter());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    @Override

    protected void onPause() {
        super.onPause();
        hexiwearService.readCharStop();
        unregisterReceiver(mGattUpdateReceiver);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////1//////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    @Override

    protected void onDestroy() {

        super.onDestroy();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    private void displayCharData(String uuid, byte[] data) {
        int tmpLong;
        float tmpFloat;

        if (uuid.equals(HexiwearService.UUID_CHAR_ACCEL)) {
            tmpLong = (((int)data[1]) << 8) | (data[0] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            progressBarX.setProgressTitle(String.valueOf(tmpFloat)+"g");
            tmpLong += (progressBarX.getProgressMax() >> 1);
            if(tmpLong > progressBarX.getProgressMax()) {
                tmpLong = progressBarX.getProgressMax();
            }
            progressBarX.setProgressValue(tmpLong);

            tmpLong = (((int)data[3]) << 8) | (data[2] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            progressBarY.setProgressTitle(String.valueOf(tmpFloat)+"g");

            tmpLong += (progressBarY.getProgressMax() >> 1);
            if(tmpLong > progressBarY.getProgressMax()) {
                tmpLong = progressBarY.getProgressMax();
            }
            progressBarY.setProgressValue(tmpLong);

            tmpLong = (((int)data[5]) << 8) | (data[4] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            progressBarZ.setProgressTitle(String.valueOf(tmpFloat)+"g");
            tmpLong += (progressBarZ.getProgressMax() >> 1);
            if(tmpLong > progressBarZ.getProgressMax()) {
                tmpLong = progressBarZ.getProgressMax();
            }
            progressBarZ.setProgressValue(tmpLong);
        }

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    private static IntentFilter makeGattUpdateIntentFilter() {
        final IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(BluetoothLeService.ACTION_GATT_DISCONNECTED);
        intentFilter.addAction(BluetoothLeService.ACTION_DATA_AVAILABLE);
        return intentFilter;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Handles various events fired by the Service.
    // ACTION_GATT_DISCONNECTED: disconnected from a GATT server.
    // ACTION_DATA_AVAILABLE: received data from the device.  This can be a result of read
    //                        or notification operations.

    private final BroadcastReceiver mGattUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            if (BluetoothLeService.ACTION_GATT_DISCONNECTED.equals(action)) {
                invalidateOptionsMenu();
                Intent intentAct = new Intent(AccelActivity.this, DeviceScanActivity.class);
                startActivity(intentAct);
            } else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action)) {

                byte[] data = intent.getByteArrayExtra(BluetoothLeService.EXTRA_DATA);
                String uuid = intent.getStringExtra(BluetoothLeService.EXTRA_CHAR);

                displayCharData(uuid, data);
            }
        }
    };
}
