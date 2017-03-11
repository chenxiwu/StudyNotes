package com.example.sy.testintent;

import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

/**
 * Created by SY on 2016/12/18.
 */

public class SecondActivity extends AppCompatActivity {
    TextView textView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        textView = (TextView)findViewById(R.id.textViewId);

        Intent intent = getIntent();
        int age = intent.getIntExtra("com.example.sy.testIntent.Age", 10);

        String name = intent.getStringExtra("com.example.sy.testIntent.Name");
        textView.setText(name + ":" + age);
    }
}
