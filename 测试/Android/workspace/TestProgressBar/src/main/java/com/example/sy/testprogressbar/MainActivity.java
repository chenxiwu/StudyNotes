package com.example.sy.testprogressbar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;

public class MainActivity extends AppCompatActivity {
    ProgressBar progressBar;
    Button increaseButton;
    Button decreaseButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        progressBar = (ProgressBar)this.findViewById(R.id.roundProgressBarId);
        //设置绝对进度
        progressBar.setProgress(25);
        //progressBar.setSecondaryProgress(75);
        /*
        boolean flag = progressBar.isIndeterminate();
        System.out.println(flag);
        */

        increaseButton = (Button)this.findViewById(R.id.increseButton);
        increaseButton.setOnClickListener(new ButtonListener());

        decreaseButton = (Button)this.findViewById(R.id.decreaseButton);
        decreaseButton.setOnClickListener(new ButtonListener());
    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            switch (view.getId()) {
                case R.id.increseButton:
                    progressBar.incrementProgressBy(5);
                    break;
                case R.id.decreaseButton:
                    progressBar.setProgress(progressBar.getProgress() - 5);
                    break;
            }
        }
    }
}
