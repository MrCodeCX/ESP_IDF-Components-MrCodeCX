#include <driver_motor_drv8871.h>
#include <d_m_drv8871_internal.h>


// SETUP

esp_err_t d_m_drv8871_setup()
{
    ESP_ERROR_CHECK(d_m_drv8871_internal_setup_mcpwm());

    return ESP_OK;
}


// WRITE

esp_err_t d_m_drv8871_write(float write_a, float write_b)
{
    // With float write from -1 to 1
    float duty_a = d_m_drv8871_internal_map_pwm(write_a);
    float duty_b = d_m_drv8871_internal_map_pwm(write_b);

    // Motor A
    if (write_a > 0) d_m_drv8871_internal_write_motor_a_positive_mode_up(duty_a);
    else if (write_a < 0) d_m_drv8871_internal_write_motor_a_negative_mode_up(duty_a);
    else d_m_drv8871_internal_write_motor_a_zero_mode_up(duty_a);

    // Motor B
    if (write_b > 0) d_m_drv8871_internal_write_motor_b_positive_mode_up(duty_b);
    else if (write_b < 0) d_m_drv8871_internal_write_motor_b_negative_mode_up(duty_b);
    else d_m_drv8871_internal_write_motor_b_zero_mode_up(duty_b);

    return ESP_OK;
}