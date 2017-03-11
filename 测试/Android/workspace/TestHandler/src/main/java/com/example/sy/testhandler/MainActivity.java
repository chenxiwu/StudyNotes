package com.example.sy.testhandler;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button button;
    private Handler handler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button = (Button)findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());

        handler = new FirstHander();
    }

    class ButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            //获取消息对象
            Message msg = handler.obtainMessage();
            msg.what = 4;
            //发送消息
            handler.sendMessage(msg);
        }
    }

    class FirstHander extends Handler {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            System.out.println(msg.what);
        }
    }
}
