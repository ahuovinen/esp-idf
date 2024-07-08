#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/ledc.h>

#define LEDC_LED1 12
#define LEDC_LED2 13


void app_main(void)
{
    ledc_timer_config_t timer_config = {};

    timer_config.duty_resolution    = LEDC_TIMER_13_BIT;
    timer_config.freq_hz            = 4000;
    timer_config.speed_mode         = LEDC_LOW_SPEED_MODE;
    timer_config.timer_num          = LEDC_TIMER_0;
    timer_config.clk_cfg            = LEDC_AUTO_CLK;

    ledc_timer_config(&timer_config);

    ledc_channel_config_t channel_config = {};

    channel_config.gpio_num             = LEDC_LED1;
    channel_config.speed_mode           = LEDC_LOW_SPEED_MODE;
    channel_config.channel              = LEDC_CHANNEL_0;
    channel_config.intr_type            = LEDC_INTR_DISABLE;
    channel_config.timer_sel            = LEDC_TIMER_0;
    channel_config.duty                 = 0;
    channel_config.hpoint               = 0;
    channel_config.flags.output_invert  = 0;
  

    ledc_channel_config(&channel_config);

    while(1) {
        for(int i=0 ; i < 2000; i+= 50){
            ledc_set_duty(channel_config.speed_mode, channel_config.channel, i);
            ledc_update_duty(channel_config.speed_mode, channel_config.channel);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            printf("getting brighter duty value %d\n", i);
        }
        
        for(int i=2000; i > 0; i-= 50) {
            ledc_set_duty(channel_config.speed_mode, channel_config.channel, i);
            ledc_update_duty(channel_config.speed_mode, channel_config.channel);
            printf("fading duty value %d\n", i);

            vTaskDelay(50 / portTICK_PERIOD_MS);
        }
    }  
}