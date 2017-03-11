package com.master.sy.tiny4412;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    Button ledButton;
    Button adcButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ButtonListener buttonListener = new ButtonListener();
        ledButton = (Button)findViewById(R.id.ledButtonId);
        ledButton.setOnClickListener(buttonListener);

        adcButton = (Button)findViewById(R.id.adcButtonId);
        adcButton.setOnClickListener(buttonListener);
    }

    private class ButtonListener implements View.OnClickListener {
        Intent intent;

        @Override
        public void onClick(View view) {
            switch (view.getId()) {
                case R.id.ledButtonId:
                    intent = new Intent();
                    intent.setClass(MainActivity.this, LedActivity.class);
                    startActivity(intent);
                    break;

                case R.id.adcButtonId:
                    intent = new Intent();
                    intent.setClass(MainActivity.this, AdcActivity.class);
                    startActivity(intent);
                    break;
            }
        }
    }
}
