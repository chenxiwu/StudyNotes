package com.example.sy.testratingbar;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.RatingBar;
import android.widget.RatingBar.OnRatingBarChangeListener;

public class MainActivity extends AppCompatActivity {
    RatingBar ratingBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ratingBar = (RatingBar)this.findViewById(R.id.ratingBarId);
        ratingBar.setOnRatingBarChangeListener(new RatingBarListener());
    }

    class RatingBarListener implements OnRatingBarChangeListener {

        @Override
        public void onRatingChanged(RatingBar ratingBar, float progress, boolean fromUser) {
            System.out.println("Progress：" + progress + " FromUser：" + fromUser);
        }
    }
}
