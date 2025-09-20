#include "main.h"
#include "UartLink.hpp"
#include "message.hpp"
#include "sg90.hpp"
#include "LED.hpp"

// $$$$ 配線方法　$$$$
/*
    F446RE用の基板につなぐ際、PWMピンとGNDピンをつなぐ必要がある
*/


// ---- UART ----
extern UART_HandleTypeDef huart2;

// ---- servo ----
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;

// ---- LED ----
LED led(GPIOB, GPIO_PIN_3);

// ==== 対ROS通信 ====
UartLink uart_link(&huart2);
Publisher<UartLink, float, float, float, float, float, float>periodic_pub(uart_link, messages::transmission::PERIODIC);
//データの送信, publisherの設定
UartLinkPublisher<float> pub(uart_link, 1);
//データの受信, subscriberの設定
UartLinkSubscriber<bool> sub_catch1(uart_link, 1);
UartLinkSubscriber<bool> sub_catch2(uart_link, 2);

// ---- SG90 servo motor ----
ServoMotor sg90_1(&htim1, TIM_CHANNEL_1);
ServoMotor sg90_2(&htim1, TIM_CHANNEL_2);
ServoMotor sg90_3(&htim1, TIM_CHANNEL_3);
ServoMotor sg90_4(&htim2, TIM_CHANNEL_1);
ServoMotor sg90_5(&htim2, TIM_CHANNEL_2);
ServoMotor sg90_6(&htim2, TIM_CHANNEL_4);

// ==== 割り込みハンドラ ====
// UARTの割り込みハンドラ
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2) // USART2の割り込み
    {
        uart_link.interrupt(); // UartLinkの割り込み処理を呼ぶ.os2との通信で受信したデータを処理
    }
}
// パブリッシャーのコールバック関数
void pub_callback(float data)
{
    periodic_pub.publish(data, data, data, data, data, data);
}
// // サブスクライバのコールバック関数
// void sub_catch1_callback(bool servo_1_2_3_4_data)
// {
//     if(servo_1_2_3_4_data == true)
//     {
//         for (int angle = 90; angle <=175; angle += 3){
//             sg90_1.SetAngle(angle);
//             sg90_2.SetAngle(angle);
//             sg90_3.SetAngle(angle);
//             sg90_4.SetAngle(angle);
//             HAL_Delay(15);
//         }
//     }
// }
// ==== setupとloop関数 ====
void setup()
{
    uart_link.start(); //ros2との通信を開始
    // // ---- SG90を初期化 ----
    // sg90_1.start();
    // sg90_2.start();
    // sg90_3.start();
    // sg90_4.start();
    // sg90_5.start();
    // sg90_6.start();

    // // ---- LEDを初期化 ----
    // led.off();
}

void loop()
{
    float value = 3.14f;

    // 通常の float publish
    pub.publish(value);

    // periodic_pub も同時に publish
    pub_callback(value);

    // // int angle = 45;
    // // sg90_1.SetAngle(angle);
    // // sg90_2.SetAngle(angle);
    // // sg90_3.SetAngle(angle);
    // // sg90_4.SetAngle(angle);
    // // sg90_5.SetAngle(angle);
    // // sg90_6.SetAngle(angle);
    // // HAL_Delay(2000);
    
    // // ---- SG90を0度から180度まで動かす ----
    // for(int angle = 100; angle <= 120; angle += 3){
    //     sg90_1.SetAngle(angle);
    //     sg90_2.SetAngle(angle);
    //     sg90_3.SetAngle(angle);
    //     sg90_4.SetAngle(angle);
    //     sg90_5.SetAngle(angle);
    //     sg90_6.SetAngle(angle);
    //     HAL_Delay(20);
    // }
    // // // angle = 175;
    // // // sg90_1.SetAngle(angle);
    // // // sg90_2.SetAngle(angle);
    // // // sg90_3.SetAngle(angle);
    // // // sg90_4.SetAngle(angle);
    // // // sg90_5.SetAngle(angle);
    // // // sg90_6.SetAngle(angle);
    // HAL_Delay(3000);

    // // ---- SG90を0度から180度まで動かす ----
    // for(int angle = 120; angle >= 100; angle -= 3){
    //     sg90_1.SetAngle(angle);
    //     sg90_2.SetAngle(angle);
    //     sg90_3.SetAngle(angle);
    //     sg90_4.SetAngle(angle);
    //     sg90_5.SetAngle(angle);
    //     sg90_6.SetAngle(angle);
    //     HAL_Delay(20);
    // }
    // HAL_Delay(100);
}