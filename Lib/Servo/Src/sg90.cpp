#include "sg90.hpp"
#include "main.h"
#include "LED.hpp"

//ServoMotor::ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel, LED *indicatorLED) {
ServoMotor::ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel) {
    this->htim = htim;
    this->channel = channel;
    //this->indicatorLED = nullptr;
}
    
// PWM信号の出力を開始
void ServoMotor::start() {
    HAL_TIM_PWM_Start(htim, channel);
    // //LEDがある場合は一回点滅
    // if(indicatorLED != nullptr){
    //     indicatorLED->toggle();
    //     HAL_Delay(200);
    //     indicatorLED->toggle();
    // }
}

// 角度を設定
void ServoMotor::SetAngle(int angle) {
    if (angle < MIN_Angle) {
        angle = MIN_Angle;
    } else if (angle > MAX_Angle) {
        angle = MAX_Angle;
    }

    // パルス幅を計算
    int pulse_width_us = MIN_Pulse_Width_us + (MAX_Pulse_Width_us - MIN_Pulse_Width_us) * angle / (MAX_Angle - MIN_Angle);
    
    // パルス幅を設定
    __HAL_TIM_SET_COMPARE(htim, channel, pulse_width_us);
    //APB1 Timer Clock = 8MHz
    //Prescaler = 8-1
    //Period = 20000-1
    //PWM Frequency = 8MHz / (8 * 20000) = 50Hz = 20ms

    // //LEDがある場合は3回点滅
    // if(indicatorLED != nullptr){
    //     for(int i=0; i<3; i++){
    //         indicatorLED->toggle();
    //         HAL_Delay(200);
    //         indicatorLED->toggle();
    //         HAL_Delay(200);
    //     }
    //     indicatorLED->off();
    // }
}