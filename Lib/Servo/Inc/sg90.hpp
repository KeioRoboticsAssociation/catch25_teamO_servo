#pragma once

#include "stm32f3xx_hal.h"
#include <stdint.h>
#include "tim.h"
// #include "LED.hpp"


class ServoMotor{
    private:
        TIM_HandleTypeDef *htim;
        uint32_t channel;

        // LED *indicatorLED;
        static constexpr int MIN_Pulse_Width_us = 500; //0.5ms = 500us
        static constexpr int MAX_Pulse_Width_us = 2400; //2.4ms = 2400us
        static constexpr int MIN_Angle = 0;
        static constexpr int MAX_Angle = 180;

    public:
        ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel);
        // ServoMotor(TIM_HandleTypeDef *htim, uint32_t channel, LED *indicatorLED = nullptr);
        void SetAngle(int angle);
        void start();
};