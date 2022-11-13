#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../../fsm/debounce_fsm.h"
#include "../../fsm/rising_edge_fsm.h"
#include "../../fsm/slide_fsm.h"

#define OUTPUT_PINS (1ULL << GPIO_NUM_16 | 1ULL << GPIO_NUM_17 | 1ULL << GPIO_NUM_18 | 1ULL << GPIO_NUM_19)
#define INPUT_PINS (1ULL << GPIO_NUM_22 | 1ULL << GPIO_NUM_23)

void ReadButtonTask(void *pvParam)
{

    int left_debounce_state = IDLE_STATE, left_debounce_counter = 0, left_debounce_output = 0;
    int right_debounce_state = IDLE_STATE, right_debounce_counter = 0, right_debounce_output = 0;

    int left_rising_edge_state = LOW_STATE, left_input = 0;
    int right_rising_edge_state = LOW_STATE, right_input = 0;

    int slide_state = 1;

    TickType_t xDelay = 10 / portTICK_PERIOD_MS;

    for (;;)
    {
        TickType_t xLastWakeTime = xTaskGetTickCount();

        // debouncing
        debounce_fsm(&left_debounce_state, &left_debounce_counter, gpio_get_level(GPIO_NUM_23), &left_debounce_output);
        debounce_fsm(&right_debounce_state, &right_debounce_counter, gpio_get_level(GPIO_NUM_22), &right_debounce_output);

        // detect rising edge
        rising_edge_fsm(&left_rising_edge_state, left_debounce_output, &left_input);
        rising_edge_fsm(&right_rising_edge_state, right_debounce_output, &right_input);

        // slide LED
        slide_fsm(&slide_state, left_input, right_input);
        REG_WRITE(GPIO_OUT_REG, slide_state << 16);

        xTaskDelayUntil(&xLastWakeTime, xDelay);
    }
}

void app_main(void)
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pin_bit_mask = INPUT_PINS;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpio_config(&io_conf);

    io_conf.pin_bit_mask = OUTPUT_PINS;
    io_conf.mode = GPIO_MODE_OUTPUT;
    gpio_config(&io_conf);

    xTaskCreatePinnedToCore(ReadButtonTask, "Read Button Task", 2048, NULL, 2, NULL, 0);
}
