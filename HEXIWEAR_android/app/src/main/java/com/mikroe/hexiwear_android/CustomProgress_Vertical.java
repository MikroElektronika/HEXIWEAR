package com.mikroe.hexiwear_android;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

/**
 * Created by djolic on 2015-11-05.
 */
public class CustomProgress_Vertical extends LinearLayout {

    private TextView txtView_value;
    private VerticalSeekBar seekBar;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor

    public CustomProgress_Vertical(Context context, AttributeSet attrs) {
        super(context, attrs, 0);

        TypedArray a;
        String     attr;

        TextView txtView_axis;
        TextView txtView_max;
        TextView txtView_min;

        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.custom_progress_vertical_layout, this);

        txtView_axis = (TextView) findViewById(R.id.textView_axis);
        txtView_max = (TextView) findViewById(R.id.textView_max);
        txtView_min = (TextView) findViewById(R.id.textView_min);
        txtView_value = (TextView) findViewById(R.id.textView_value);

        seekBar = (VerticalSeekBar) findViewById(R.id.verticalProgressbar);

        a = context.obtainStyledAttributes(attrs, R.styleable.CustomProgress_Vertical);

        setStringAttribute(txtView_axis, a.getString(R.styleable.CustomProgress_Vertical_label_axis), "axis");
        setStringAttribute(txtView_max, a.getString(R.styleable.CustomProgress_Vertical_label_max), "100");
        setStringAttribute(txtView_min, a.getString(R.styleable.CustomProgress_Vertical_label_min), "0");
        setStringAttribute(txtView_value, a.getString(R.styleable.CustomProgress_Vertical_label_value), "50");

        attr = a.getString(R.styleable.CustomProgress_Vertical_progress_vertical);
        if(attr != null) {
            this.setProgressValue(Integer.parseInt(attr));
        }
        else {
            this.setProgressValue(50);
        }

        attr = a.getString(R.styleable.CustomProgress_Vertical_max_progress_vertical);
        if(attr != null) {
            seekBar.setMax(Integer.parseInt(attr));
            seekBar.setSecondaryProgress(Integer.parseInt(attr));
        }
        else {
            seekBar.setMax(100);
            seekBar.setSecondaryProgress(100);
        }

    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Set functions

    public void setProgressValue(int i) {
        seekBar.setProgress(i);
    }

    public void setProgressTitle(String strValue) {
        txtView_value.setText(strValue);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Get functions

    public Integer getProgressMax() {
        return seekBar.getMax();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Private functions

    private void setStringAttribute(TextView txtView, String attr, String defaultStr) {

        if(attr != null) {
            txtView.setText(attr);
        }
        else {
            txtView.setText(defaultStr);
        }
    }
}
