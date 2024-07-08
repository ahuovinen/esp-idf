#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define GPIO_LED1 12
#define GPIO_LED2 13
#define GPIO_PIN_SEL ((1ULL<<GPIO_LED1) | (1ULL<<GPIO_LED2));



void app_main(void)
{
    gpio_config_t outputleds = {};

    outputleds.mode         = GPIO_MODE_OUTPUT;
    outputleds.intr_type    = GPIO_INTR_DISABLE;
    outputleds.pull_down_en = 0;
    outputleds.pull_up_en   = 0;
    outputleds.pin_bit_mask = GPIO_PIN_SEL;

    gpio_config(&outputleds);

    int level = 0 ;


    while(1) {
        gpio_set_level(GPIO_LED1, level);
        level = !level;
        
        gpio_set_level(GPIO_LED2, level);
        vTaskDelay(1000 / portTICK_PERIOD_MS);    
    };
}
