package com.example.sy.testlifecycle;

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
        System.out.println("[MainActivity] OnCreate");

        button = (Button)findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());

    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            Intent intent = new Intent();
            intent.setClass(MainActivity.this, SecondActivity.class);
            startActivity(intent);
        }
    }

    @Override
    protected void onStart() {
        super.onStart();

        System.out.println("[MainActivity] OnStart");
    }

    @Override
    protected void onResume() {
        super.onResume();

        System.out.println("[MainActivity] OnResume");
    }

    @Override
    protected void onPause() {
        super.onPause();

        System.out.println("[MainActivity] OnPause");
    }

    @Override
    protected void onStop() {
        super.onStop();

        System.out.println("[MainActivity] OnStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        System.out.println("[MainActivity] OnDestroy");
    }

    @Override
    protected void onRestart() {
        super.onRestart();

        System.out.println("[MainActivity] OnRestart");
    }
}
