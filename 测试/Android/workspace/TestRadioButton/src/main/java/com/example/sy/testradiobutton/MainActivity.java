package com.example.sy.testradiobutton;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.RadioButton;
import android.widget.RadioGroup;

public class MainActivity extends AppCompatActivity {
    private RadioGroup sexRadioGroup;
    private RadioButton maleRadioButton;
    private RadioButton femaleRadioButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sexRadioGroup = (RadioGroup)this.findViewById(R.id.sexRadioGroupId);
        maleRadioButton = (RadioButton)this.findViewById(R.id.maleRadioButton);
        femaleRadioButton = (RadioButton)this.findViewById(R.id.femaleRadioButton);

        maleRadioButton.setOnCheckedChangeListener(new RadioButtonListener());
        femaleRadioButton.setOnCheckedChangeListener(new RadioButtonListener());
        /*
        RadioGroupListener radioGroupListener = new RadioGroupListener();
        sexRadioGroup.setOnCheckedChangeListener(radioGroupListener);
        */
    }

    class RadioButtonListener implements CompoundButton.OnCheckedChangeListener {

        @Override
        public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
            if (compoundButton.getId() == maleRadioButton.getId()) {
                if (b == true) {
                    System.out.println("男性选中");
                } else {
                    System.out.println("男性取消选中");
                }
            } else if (compoundButton.getId() == femaleRadioButton.getId()) {
                if (b == true) {
                    System.out.println("女性选中");
                } else {
                    System.out.println("女性取消选中");
                }
            }
        }
    }

    class RadioGroupListener implements RadioGroup.OnCheckedChangeListener {

        @Override
        public void onCheckedChanged(RadioGroup radioGroup, int id) {
            if (id == maleRadioButton.getId()) {
                System.out.println("男性");
            } else if (id == femaleRadioButton.getId()){
                System.out.println("女性");
            }
        }
    }
}
