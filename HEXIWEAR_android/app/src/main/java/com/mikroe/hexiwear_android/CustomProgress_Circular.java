package com.mikroe.hexiwear_android;

import android.content.Context;
import android.content.res.TypedArray;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.ProgressBar;
import android.widget.RelativeLayout;
import android.widget.TextView;

/**
 * Created by djolic on 2015-11-05.
 */
public class CustomProgress_Circular extends RelativeLayout {

    private TextView txtView_label_2;
    private ProgressBar progressBar;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructor

    public CustomProgress_Circular(Context context, AttributeSet attrs) {

        super(context, attrs, 0);

        TextView txtView_label_1;
        TextView txtView_label_3;

        TextView txtView_start;
        TextView txtView_firstQuarter;
        TextView txtView_half;
        TextView txtView_thirdQuarter;

        TypedArray a;
        String     attr;

        LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.custom_progress_circular_layout, this);

        txtView_label_1 = (TextView) findViewById(R.id.textView_Label1);
        txtView_label_2 = (TextView) findViewById(R.id.textView_Label2);
        txtView_label_3 = (TextView) findViewById(R.id.textView_Label3);

        txtView_start = (TextView) findViewById(R.id.textView_StartValue);
        txtView_half = (TextView) findViewById(R.id.textView_Half);
        txtView_firstQuarter = (TextView) findViewById(R.id.textview_FirstQuarter);
        txtView_thirdQuarter = (TextView) findViewById(R.id.textView_ThirdQuarter);

        progressBar = (ProgressBar) findViewById(R.id.circularProgressbar);

        a = context.obtainStyledAttributes(attrs, R.styleable.CustomProgress_Circular);

        setStringAttribute(txtView_label_1, a.getString(R.styleable.CustomProgress_Circular_label_1), "axis");
        setStringAttribute(txtView_label_2, a.getString(R.styleable.CustomProgress_Circular_label_2), "value");
        setStringAttribute(txtView_label_3, a.getString(R.styleable.CustomProgress_Circular_label_3), "units");
        setStringAttribute(txtView_start, a.getString(R.styleable.CustomProgress_Circular_start_value), "0");
        setStringAttribute(txtView_firstQuarter, a.getString(R.styleable.CustomProgress_Circular_first_quarter_value), "+128");
        setStringAttribute(txtView_half, a.getString(R.styleable.CustomProgress_Circular_half_value), "-256+");
        setStringAttribute(txtView_thirdQuarter, a.getString(R.styleable.CustomProgress_Circular_third_quarter_value), "-128");

        attr = a.getString(R.styleable.CustomProgress_Circular_progress_circular);
        if(attr != null) {
            progressBar.setProgress(Integer.parseInt(attr));
        }
        else {
            progressBar.setProgress(0);
        }

        attr = a.getString(R.styleable.CustomProgress_Circular_max_progress_circular);
        if(attr != null) {
            progressBar.setMax(Integer.parseInt(attr));
        }
        else {
            progressBar.setMax(100);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Set functions

    public void setProgressValue(Integer i) {
        progressBar.setProgress(i);
    }

    public void setProgressTitle(String strValue) {
        txtView_label_2.setText(strValue);
    }

    public void setProgressRotation(float rotation) {
        progressBar.setRotation(rotation);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Get functions

    public Integer getProgressMax() {
        return progressBar.getMax();
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
