package com.example.sy.stonescissorcloth;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    RadioGroup leftRadioGroup;
    RadioGroup rightRadioGroup;

    Button confirmButton;
    TextView testResultText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        leftRadioGroup = (RadioGroup)this.findViewById(R.id.leftRadioGroupId);
        rightRadioGroup = (RadioGroup)this.findViewById(R.id.rightRadioGroupId);
        confirmButton = (Button)this.findViewById(R.id.confirmButtonId);
        confirmButton.setOnClickListener(new ConfirmButtonListener());
        testResultText = (TextView)this.findViewById(R.id.testResultTextId);
    }

    class ConfirmButtonListener implements View.OnClickListener {

        @Override
        public void onClick(View view) {
            MorraType leftMorraType;
            MorraType rightMorraType;

            Button button = (Button)view;
            if (button.getId() == confirmButton.getId()) {
                switch (leftRadioGroup.getCheckedRadioButtonId()) {
                    case R.id.leftStoneRadioButtonId:
                        leftMorraType = MorraType.STONE;
                        break;
                    case R.id.leftScissorRadioButtonId:
                        leftMorraType = MorraType.SCISSOR;
                        break;
                    case R.id.leftClothRadioButtonId:
                        leftMorraType = MorraType.CLOTH;
                        break;
                    default:
                        return;
                }

                switch (rightRadioGroup.getCheckedRadioButtonId()) {
                    case R.id.rightStoneRadioButtonId:
                        rightMorraType = MorraType.STONE;
                        break;
                    case R.id.rightScissorRadioButtonId:
                        rightMorraType = MorraType.SCISSOR;
                        break;
                    case R.id.rightClothRadioButtonId:
                        rightMorraType = MorraType.CLOTH;
                        break;
                    default:
                        return;
                }

                int result = this.compare(leftMorraType, rightMorraType);
                if (result > 0) {
                    testResultText.setText("美女获胜");
                } else if (result == 0) {
                    testResultText.setText("平局");
                } else {
                    testResultText.setText("机器人获胜");
                }
            }
        }

        public int compare(MorraType a, MorraType b) {
            switch (a) {
                case STONE:
                    if (b == MorraType.STONE) {
                        return 0;
                    } else if (b == MorraType.SCISSOR) {
                        return 1;
                    } else if (b == MorraType.CLOTH) {
                        return -1;
                    }
                    break;
                case SCISSOR:
                    if (b == MorraType.STONE) {
                        return -1;
                    } else if (b == MorraType.SCISSOR) {
                        return 0;
                    } else if (b == MorraType.CLOTH) {
                        return 1;
                    }
                    break;
                case CLOTH:
                    if (b == MorraType.STONE) {
                        return 1;
                    } else if (b == MorraType.SCISSOR) {
                        return -1;
                    } else if (b == MorraType.CLOTH) {
                        return 0;
                    }
                    break;
                default:
                    return 0;
            }

            return 0;
        }
    }
}
