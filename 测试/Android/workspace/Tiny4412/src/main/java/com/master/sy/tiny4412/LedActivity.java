package com.master.sy.tiny4412;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import com.friendlyarm.AndroidSDK.*;

/**
 * Created by SY on 2016/12/24.
 */

public class LedActivity extends AppCompatActivity {
    private CheckBox[] ledCheckBox = new CheckBox[4];
    private CheckBox ledAllCheckBox;
    private CheckBox flowLedCheckBox;
    private static final int LED_NUMS = 4;
    private FlowLedThread flowLedThread;

    private CheckBoxListener checkBoxListener = new CheckBoxListener();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_led);

        ledCheckBox[0] = (CheckBox)findViewById(R.id.led1CheckBoxId);
        ledCheckBox[0].setOnCheckedChangeListener(checkBoxListener);
        ledCheckBox[1] = (CheckBox)findViewById(R.id.led2CheckBoxId);
        ledCheckBox[1].setOnCheckedChangeListener(checkBoxListener);
        ledCheckBox[2] = (CheckBox)findViewById(R.id.led3CheckBoxId);
        ledCheckBox[2].setOnCheckedChangeListener(checkBoxListener);
        ledCheckBox[3] = (CheckBox)findViewById(R.id.led4CheckBoxId);
        ledCheckBox[3].setOnCheckedChangeListener(checkBoxListener);
        ledAllCheckBox = (CheckBox)findViewById(R.id.ledAllCheckBoxId);
        ledAllCheckBox.setOnCheckedChangeListener(checkBoxListener);
        new Thread(new CheckBoxThread()).start();

        flowLedCheckBox = (CheckBox)findViewById(R.id.flowLedId);
        flowLedCheckBox.setOnCheckedChangeListener(checkBoxListener);
        flowLedThread = new FlowLedThread();
        new Thread(flowLedThread).start();

        for (int i=1; i<=ledCheckBox.length; ++i) {
            setLedStatus(i, false);
        }
    }

    public static Boolean setLedStatus(int led, Boolean status) {
        int ledBase = 0;
        int level = (status == true) ? GPIOEnum.HIGH : GPIOEnum.LOW;

        if ((led >= 1) && (led <= LED_NUMS)) {
            HardwareControler.setLedState(ledBase + led - 1, level);
            return true;
        } else {
            return false;
        }
    }

    /**
     * 多选框线程
     */
    private class CheckBoxThread implements Runnable {

        @Override
        public void run() {

            while (true) {
                ;
            }
        }
    }

    /**
     * 流水灯线程
     */
    private class FlowLedThread implements Runnable {
        private Boolean flagRun = false;
        private int ledIndex = 0;

        public Boolean getFlagRun() {
            return flagRun;
        }

        public void setFlagRun(Boolean flagRun) {
            this.flagRun = flagRun;
        }

        @Override
        public void run() {
            while (true) {
                if (flagRun == false) {
                    continue;
                } else {
                    if (++ledIndex > LED_NUMS) {
                        ledIndex = 1;
                    }

                    for (int i=1; i<=LED_NUMS; ++i) {
                        if (i == ledIndex) {
                            setLedStatus(i, true);
                        } else {
                            setLedStatus(i, false);
                        }
                    }

                    try {
                        Thread.sleep(1000);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    /**
     * 多选框监听器
     */
    private class CheckBoxListener implements CompoundButton.OnCheckedChangeListener {

        @Override
        public void onCheckedChanged(CompoundButton compoundButton, boolean status) {
            CheckBox checkBox = (CheckBox)compoundButton;

            switch(checkBox.getId()) {
                case R.id.led1CheckBoxId:
                    setLedStatus(1, status);
                    break;
                case R.id.led2CheckBoxId:
                    setLedStatus(2, status);
                    break;
                case R.id.led3CheckBoxId:
                    setLedStatus(3, status);
                    break;
                case R.id.led4CheckBoxId:
                    setLedStatus(4, status);
                    break;
                case R.id.ledAllCheckBoxId:
                    for (int i=0; i<ledCheckBox.length; ++i) {
                        ledCheckBox[i].setChecked(status);
                    }
                    break;
                case R.id.flowLedId:
                    if (status == true) {
                        flowLedThread.setFlagRun(true);
                    } else {
                        flowLedThread.setFlagRun(false);
                    }
                    break;
            }
        }
    }
}
