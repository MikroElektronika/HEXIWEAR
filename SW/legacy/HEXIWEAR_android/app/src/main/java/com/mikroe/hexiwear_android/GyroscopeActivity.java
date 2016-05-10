package com.mikroe.hexiwear_android;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.util.ArrayList;

public class GyroscopeActivity extends Activity {

    private CustomProgress_Circular progressBarX;
    private CustomProgress_Circular progressBarY;
    private CustomProgress_Circular progressBarZ;

    private HexiwearService hexiwearService;

    private final ArrayList<String> uuidArray = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.gyroscope_screen);

        uuidArray.add(HexiwearService.UUID_CHAR_GYRO);

        progressBarX = (CustomProgress_Circular) findViewById(R.id.gyroProgressX);
        progressBarY = (CustomProgress_Circular) findViewById(R.id.gyroProgressY);
        progressBarZ = (CustomProgress_Circular) findViewById(R.id.gyroProgressZ);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    @Override

    protected void onResume() {
        super.onResume();

        hexiwearService = new HexiwearService(uuidArray);
        hexiwearService.readCharStart(50);
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
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    @Override

    protected void onDestroy() {

        super.onDestroy();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    private void displayData(TextView txtView, String data) {
        if (data != null) {
            txtView.setText(data);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    private void displayCharData(String uuid, byte[] data) {
        String tmpString;
        int tmpLong;

        if (uuid.equals(HexiwearService.UUID_CHAR_GYRO)) {
            tmpLong = (((int)data[1]) << 8) | (data[0] & 0xff);
            progressBarX.setProgressTitle(String.valueOf(tmpLong));
            if(tmpLong < 0) {
                progressBarX.setProgressRotation((tmpLong / ((float) progressBarX.getProgressMax()) * 360f));
                tmpLong = -tmpLong;
            }
            else {
                progressBarX.setProgressRotation(0);
            }
            progressBarX.setProgressValue(tmpLong);

            tmpLong = (((int)data[3]) << 8) | (data[2] & 0xff);
            progressBarY.setProgressTitle(String.valueOf(tmpLong));
            if(tmpLong < 0) {
                progressBarY.setProgressRotation((tmpLong / ((float) progressBarY.getProgressMax()) * 360f));
                tmpLong = -tmpLong;
            }
            else {
                progressBarY.setProgressRotation(0);
            }
            progressBarY.setProgressValue(tmpLong);

            tmpLong = (((int)data[5]) << 8) | (data[4] & 0xff);
            progressBarZ.setProgressTitle(String.valueOf(tmpLong));
            if(tmpLong < 0) {
                progressBarZ.setProgressRotation((tmpLong / ((float) progressBarZ.getProgressMax()) * 360f));
                tmpLong = -tmpLong;
            }
            else {
                progressBarZ.setProgressRotation(0);
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
                Intent intentAct = new Intent(GyroscopeActivity.this, DeviceScanActivity.class);
                startActivity(intentAct);
            } else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action)) {

                byte[] data = intent.getByteArrayExtra(BluetoothLeService.EXTRA_DATA);
                String uuid = intent.getStringExtra(BluetoothLeService.EXTRA_CHAR);

                displayCharData(uuid, data);
            }
        }
    };
}
