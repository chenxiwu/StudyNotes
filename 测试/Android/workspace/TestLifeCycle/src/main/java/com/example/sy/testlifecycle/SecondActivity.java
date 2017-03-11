package com.example.sy.testlifecycle;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

/**
 * Created by SY on 2016/12/18.
 */

public class SecondActivity extends AppCompatActivity{
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_second);

        System.out.println("[secondActivity] OnCreate");
    }

    @Override
    protected void onStart() {
        super.onStart();

        System.out.println("[secondActivity] OnStart");
    }

    @Override
    protected void onResume() {
        super.onResume();

        System.out.println("[secondActivity] OnResume");
    }

    @Override
    protected void onPause() {
        super.onPause();

        System.out.println("[secondActivity] OnPause");
    }

    @Override
    protected void onStop() {
        super.onStop();

        System.out.println("[secondActivity] OnStop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        System.out.println("[secondActivity] OnDestroy");
    }

    @Override
    protected void onRestart() {
        super.onRestart();

        System.out.println("[secondActivity] OnRestart");
    }
}
