#include "main.hpp"
#include "sg90.hpp"
#include "LED.hpp"

// $$$$ 配線方法　$$$$
/*
    F446RE用の基板につなぐ際、PWMピンとGNDピンをつなぐ必要がある
*/

int angle = 0;

// ---- servo ----
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

// ---- LED ----
LED led(GPIOB, GPIO_PIN_3);

// ---- SG90 servo motor ----
ServoMotor sg90_1(&htim1, TIM_CHANNEL_1);
ServoMotor sg90_2(&htim1, TIM_CHANNEL_2);
ServoMotor sg90_3(&htim1, TIM_CHANNEL_3);
ServoMotor sg90_4(&htim2, TIM_CHANNEL_1);
ServoMotor sg90_5(&htim2, TIM_CHANNEL_2);
ServoMotor sg90_6(&htim2, TIM_CHANNEL_4);

// ==== setupとloop関数 ====
void setup()
{
    // ---- SG90を初期化 ----
    sg90_1.start();

    // ---- LEDを初期化 ----
    led.off();
}

void loop()
{
    led.toggle();
    HAL_Delay(1000);
    // ---- SG90を0度から180度まで動かす ----
    for(int angle = 0; angle <= 180; angle += 3){
        sg90_1.SetAngle(angle);
        HAL_Delay(10);
    }
}