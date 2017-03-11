package com.example.sy.testtime;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TimePicker;

import java.util.Date;
/*
public class MainActivity extends AppCompatActivity {
    private TimePicker timePicker;
    private int hours,minutes;
    Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        timePicker = (TimePicker) this.findViewById(R.id.timeTimePickerId);
        timePicker.setIs24HourView(true);
        timePicker.setOnTimeChangedListener(new TimeListener());

        Button button = (Button)this.findViewById(R.id.getValueButtonId);
        button.setOnClickListener(new ButtonListener());
    }

    class TimeListener implements TimePicker.OnTimeChangedListener {

        @Override
        public void onTimeChanged(TimePicker timePicker, int hour, int minute) {
            if (timePicker.getId() == R.id.timeTimePickerId) {
               // System.out.println("Hour: " + hour + " Minute: " + minute);
                hours = hour;
                minutes = minute;
            }
        }
    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            System.out.println("Hour: " + hours + " Minute: " + minutes);
        }
    }
}
*/

/*
public class MainActivity extends AppCompatActivity {
    DatePicker dataPicker;
    Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dataPicker = (DatePicker)this.findViewById(R.id.dataDataPickerId);
        button = (Button)this.findViewById(R.id.buttonId);
        button.setOnClickListener(new ButtonListener());
    }

    class ButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            System.out.println("Year：" + dataPicker.getYear() + " Month：" +
                dataPicker.getMonth() + " Day：" + dataPicker.getDayOfMonth());
        }
    }
}
*/

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}