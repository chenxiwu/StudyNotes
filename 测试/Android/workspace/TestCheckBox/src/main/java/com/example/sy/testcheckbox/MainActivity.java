package com.example.sy.testcheckbox;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.CompoundButton;

public class MainActivity extends AppCompatActivity {
    CheckBox checkBoxEat;
    CheckBox checkBoxSleep;
    CheckBox checkBoxPlay;
    CheckBox checkBoxAll;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        checkBoxEat = (CheckBox)this.findViewById(R.id.checkbox_eat);
        checkBoxSleep = (CheckBox)this.findViewById(R.id.checkbox_sleep);
        checkBoxPlay = (CheckBox)this.findViewById(R.id.checkbox_play);
        checkBoxAll = (CheckBox)this.findViewById(R.id.checkbox_all);

        /*
        View.OnClickListener onClickListener = new OnBoxClickListener();
        checkBoxEat.setOnClickListener(onClickListener);
        checkBoxSleep.setOnClickListener(onClickListener);
        checkBoxPlay.setOnClickListener(onClickListener);
        */
        CheckBoxListener checkBoxListener = new CheckBoxListener();
        checkBoxEat.setOnCheckedChangeListener(checkBoxListener);
        checkBoxSleep.setOnCheckedChangeListener(checkBoxListener);
        checkBoxPlay.setOnCheckedChangeListener(checkBoxListener);
        checkBoxAll.setOnCheckedChangeListener(checkBoxListener);
    }

    class CheckBoxListener implements CompoundButton.OnCheckedChangeListener {

        @Override
        public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
            CheckBox checkBox = (CheckBox)compoundButton;

            switch(checkBox.getId()) {
                case R.id.checkbox_eat:
                    if (b == true) {
                        System.out.println("吃饭");
                    } else{
                        System.out.println("不吃饭");
                    }
                    break;
                case R.id.checkbox_sleep:
                    if (b == true) {
                        System.out.println("睡觉");
                    } else {
                        System.out.println("不睡觉");
                    }
                    break;
                case R.id.checkbox_play:
                    if (b == true) {
                        System.out.println("玩游戏");
                    } else {
                        System.out.println("不玩游戏");
                    }
                    break;
                case R.id.checkbox_all:
                    if (b == true) {
                        checkBox.setChecked(true);
                        checkBoxEat.setChecked(true);
                        checkBoxSleep.setChecked(true);
                        checkBoxPlay.setChecked(true);
                    } else {
                        checkBox.setChecked(false);
                        checkBoxEat.setChecked(false);
                        checkBoxSleep.setChecked(false);
                        checkBoxPlay.setChecked(false);
                    }
                    break;
            }
        }
    }

    class OnBoxClickListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            CheckBox checkBox = (CheckBox)view;

            switch (checkBox.getId()) {
                case R.id.checkbox_eat:
                    if (checkBox.isChecked() == true) {
                        System.out.println("吃饭");
                    } else {
                        System.out.println("不吃饭");
                    }
                    break;
                case R.id.checkbox_sleep:
                    System.out.println("睡觉");
                    break;
                case R.id.checkbox_play:
                    System.out.println("打游戏");
                    break;
            }
        }
    }
}
