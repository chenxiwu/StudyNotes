package com.example.sy.testhandler;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    Button button;
    TextView textView;
    Handler handler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button)findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());

        textView = (TextView)findViewById(R.id.textViewId);

        handler = new MyHandler();
    }

    class NetworkThread extends Thread {
        @Override
        public void run() {
            System.out.println("NetworkThread----->" + Thread.currentThread().getName());
            try {
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            String string = "从网络获取的值";
            Message msg = handler.obtainMessage();
            msg.obj = string;
            handler.sendMessage(msg);
        }
    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            NetworkThread network = new NetworkThread();
            network.start();
        }
    }

    class MyHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            textView.setText((String)msg.obj);
            System.out.println("MainThread----->" + Thread.currentThread().getName());
        }
    }
}
