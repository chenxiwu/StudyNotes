package com.example.sy.testintent;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button)findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());
    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            Intent intent = new Intent();
            intent.setClass(MainActivity.this, SecondActivity.class);
            intent.putExtra("com.example.sy.testIntent.Age", 20);
            intent.putExtra("com.example.sy.testIntent.Name", "大水猫");
            startActivity(intent);
        }
    }
}
