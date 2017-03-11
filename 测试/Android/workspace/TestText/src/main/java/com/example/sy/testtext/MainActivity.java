package com.example.sy.testtext;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView textView;
    private Button button;
    private int count = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView)this.findViewById(R.id.TextView);
        textView.setBackgroundColor(Color.BLUE);
        textView.setTextColor(Color.WHITE);

        button = (Button)this.findViewById(R.id.Button);
        button.setOnClickListener(new ButtonListener());
    }

    class ButtonListener implements View.OnClickListener {
        @Override
        public void onClick(View view) {
            count++;
            textView.setText("" + count);
        }
    }
}
