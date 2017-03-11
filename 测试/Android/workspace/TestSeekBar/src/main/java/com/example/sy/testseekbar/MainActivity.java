package com.example.sy.testseekbar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.SeekBar;

public class MainActivity extends AppCompatActivity {
    SeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        seekBar = (SeekBar)this.findViewById(R.id.seekBarId);
        seekBar.setOnSeekBarChangeListener(new SeekBarListener());
    }

    class SeekBarListener implements SeekBar.OnSeekBarChangeListener {

        @Override
        public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
            switch (seekBar.getId()) {
                case R.id.seekBarId:
                    System.out.println("Progress：" + progress + "，FromUser：" + fromUser);
                    break;
            }
        }

        @Override
        public void onStartTrackingTouch(SeekBar seekBar) {
            System.out.println("开始触摸");
        }

        @Override
        public void onStopTrackingTouch(SeekBar seekBar) {
            System.out.println("结束触摸");
        }
    }
}
