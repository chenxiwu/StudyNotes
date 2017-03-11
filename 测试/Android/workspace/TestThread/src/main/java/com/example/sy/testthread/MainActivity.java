package com.example.sy.testthread;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ProgressBar;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    TextView textView;
    Button button;
    ProgressBar progressBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView)findViewById(R.id.textViewId);
        button = (Button)findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());
        progressBar = (ProgressBar)findViewById(R.id.progressBarId);
    }

    class ButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            /*
            Thread thread = new Thread(new MyThread());
            thread.start();
            */

            //直接阻塞主线程，导致页面假死
            try {
                Thread.sleep(10 * 1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    class MyThread implements Runnable {
        @Override
        public void run() {
            try {
                //有些控件可以在Work Thread线程中修改
                for (int i=0; i<10; ++i) {
                    Thread.sleep(1000);
                    progressBar.incrementProgressBy(10);
                }
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
            //运行出现异常，只有创建视图的线程才能修改
            //textView.setText("线程修改");
        }
    }
}
