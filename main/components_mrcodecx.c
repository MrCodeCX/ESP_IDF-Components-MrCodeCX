#include <stdio.h>
#include <driver_motor_drv8871.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
    d_m_drv8871_setup();

    d_m_drv8871_write(0,0);
    vTaskDelay(pdMS_TO_TICKS(1000));
    while (1)
    {
        d_m_drv8871_write(1,1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        d_m_drv8871_write(0,0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
