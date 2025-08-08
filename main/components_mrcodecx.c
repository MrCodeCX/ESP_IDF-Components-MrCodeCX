#include <stdio.h>
#include <driver_sensor_distance_analog.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
    // Create your own config
    d_s_distance_analog_cfg_t sensor_config = {
        .adc_oneshot_cfg = (d_p_adc_oneshot_cfg_t) {
            .adc_unit = ADC_UNIT_1,
            .n_channels = 3,
            .adc_channels = {D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_35_ADC_CHANNEL, D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_32_ADC_CHANNEL, D_P_ADC_ONESHOT_CONST_ADC_1_GPIO_33_ADC_CHANNEL}
        },
        .f_conversion = d_s_distance_analog_conversion_simple_voltage
    };

    // Setup
    d_s_distance_analog_setup(&sensor_config);

    while(1) {
        // Read
        float distances[3];
        d_s_distance_analog_read_distances(&sensor_config, distances);
        printf("%f  %f  %f \n", distances[0], distances[1], distances[2]);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    // Kill
    d_s_distance_analog_kill(&sensor_config);

}
