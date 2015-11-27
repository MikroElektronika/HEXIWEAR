package com.mikroe.hexiwear_android;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.widget.TextView;

import java.util.ArrayList;

public class WeatherActivity extends Activity {

    TextView txtView_temperature;
    TextView txtView_humidity;
    TextView txtView_pressure;
    private HexiwearService hexiwearService;

    private final ArrayList<String> uuidArray = new ArrayList<String>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.weather_screen);

        uuidArray.add(HexiwearService.UUID_CHAR_TEMPERATURE);
        uuidArray.add(HexiwearService.UUID_CHAR_HUMIDITY);
        uuidArray.add(HexiwearService.UUID_CHAR_PRESSURE);

        txtView_temperature = (TextView) findViewById(R.id.textView_tempValue);
        txtView_humidity = (TextView) findViewById(R.id.textView_humValue);
        txtView_pressure = (TextView) findViewById(R.id.textView_pressValue);
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
        float tmpFloat;

        if (uuid.equals(HexiwearService.UUID_CHAR_TEMPERATURE)) {
            tmpLong = (((int)data[1]) << 8) | (data[0] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            tmpString = tmpFloat + (" \u2103");
            displayData(txtView_temperature, tmpString);
        }

        else if (uuid.equals(HexiwearService.UUID_CHAR_HUMIDITY)) {
            tmpLong = (data[1] << 8) & 0xff00 | (data[0] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            tmpString = tmpFloat + (" %");
            displayData(txtView_humidity, tmpString);
        }

        else if (uuid.equals(HexiwearService.UUID_CHAR_PRESSURE)) {
            tmpLong = (data[1] << 8) & 0xff00 | (data[0] & 0xff);
            tmpFloat = (float)tmpLong / 100;
            tmpString = tmpFloat + (" kPa");
            displayData(txtView_pressure, tmpString);
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
//                finish();
                Intent intentAct = new Intent(WeatherActivity.this, DeviceScanActivity.class);
                startActivity(intentAct);
            } else if (BluetoothLeService.ACTION_DATA_AVAILABLE.equals(action)) {

                byte[] data = intent.getByteArrayExtra(BluetoothLeService.EXTRA_DATA);
                String uuid = intent.getStringExtra(BluetoothLeService.EXTRA_CHAR);

                displayCharData(uuid, data);
            }
        }
    };
}
