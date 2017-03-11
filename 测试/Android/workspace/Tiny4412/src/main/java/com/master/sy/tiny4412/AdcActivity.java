package com.master.sy.tiny4412;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import com.friendlyarm.AndroidSDK.HardwareControler;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by SY on 2016/12/24.
 */

public class AdcActivity extends AppCompatActivity {
    private UpdateThread thread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_view);

        //开启后台更新线程
        thread = new UpdateThread();
        new Thread(thread).start();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        thread.setEscFlag(true);
    }

    //匿名类
    private Handler handler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);

            if (msg.what == 1) {
                ArrayList<ADC> arrayList = new ArrayList<ADC>();
                for (int i=0; i<4; ++i) {
                    int code = HardwareControler.readADCWithChannel(i);
                    arrayList.add(new ADC(String.format("[ADC %d]", i), code));
                }
                ListView listView = (ListView)findViewById(R.id.listViewId);
                listView.setAdapter(new ADC_ArrayAdapter(getApplicationContext(), R.layout.activity_adc, arrayList));
            }
        }
    };

    private class ADC_ArrayAdapter extends ArrayAdapter<ADC> {
        private LayoutInflater layoutInflater;
        private int resource;
        private List<ADC> list;

        public ADC_ArrayAdapter(Context context, int resource, List<ADC> objects) {
            super(context, resource, objects);
            layoutInflater = LayoutInflater.from(context);
            this.resource = resource;
            this.list = objects;
        }

        @NonNull
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if (convertView == null) {
                convertView = layoutInflater.inflate(resource, null);
            }

            TextView textView = (TextView)convertView.findViewById(R.id.adcChannelId);
            textView.setText(list.get(position).getName());
            textView = (TextView)convertView.findViewById(R.id.adcCodeId);
            textView.setText(list.get(position).getCode() + "");

            return convertView;
        }
    }

    private class ADC {
        private int code;
        private String name;

        public ADC(String name, int code) {
            this.name = name;
            this.code = code;
        }

        public int getCode() {
            return code;
        }

        public void setCode(int code) {
            this.code = code;
        }

        public String getName() {
            return name;
        }

        public void setName(String name) {
            this.name = name;
        }
    }

    private class UpdateThread implements Runnable {
        private Boolean escFlag = false;

        public void setEscFlag(Boolean escFlag) {
            this.escFlag = escFlag;
        }

        @Override
        public void run() {

            while (escFlag == false) {
                //定时发送消息
                Message msg = new Message();
                msg.what = 1;
                handler.sendMessage(msg);

                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
