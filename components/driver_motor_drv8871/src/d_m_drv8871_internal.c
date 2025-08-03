#include <d_m_drv8871_internal.h>


// INTERNAL LOGIC

float d_m_drv8871_internal_map(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


// INTERNAL MAP

float d_m_drv8871_internal_map_pwm(float value)
{
    return d_m_drv8871_internal_map_pw_mode_up(d_m_drv8871_internal_constrain(value,-1.0f, 1.0f));
}

float d_m_drv8871_internal_map_pw_mode_up(float value)
{
    // Map by absolute value, for mode_up is an inverse map -> min, max to max, min
    if(value > 0) return d_m_drv8871_internal_map(value, 0, 1, D_M_DRV8871_PWM_MAX, D_M_DRV8871_PWM_MIN);
    else if(value < 0) return d_m_drv8871_internal_map(value, 0, -1, -D_M_DRV8871_PWM_MAX, -D_M_DRV8871_PWM_MIN);
    return 0;
}


// INTERNAL SETUP

esp_err_t d_m_drv8871_internal_setup_mcpwm()
{
    ESP_ERROR_CHECK(d_m_drv8871_internal_setup_mcpwm_mode_up());

    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_setup_mcpwm_mode_up()
{
    ESP_ERROR_CHECK(d_m_drv8871_internal_setup_mcpwm_init_mode_up());
    ESP_ERROR_CHECK(d_m_drv8871_internal_setup_mcpwm_gpio_init_mode_up());

    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_setup_mcpwm_init_mode_up()
{
    mcpwm_config_t pwm_config = {
        .frequency = D_M_DRV8871_FREQ_HZ,
        .cmpr_a = 0,
        .cmpr_b = 0,
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0
    };

    ESP_ERROR_CHECK(mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config));
    ESP_ERROR_CHECK(mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &pwm_config));

    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_setup_mcpwm_gpio_init_mode_up()
{
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, D_M_DRV8871_MOTOR_A_1);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, D_M_DRV8871_MOTOR_A_2);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, D_M_DRV8871_MOTOR_B_1);
    mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0B, D_M_DRV8871_MOTOR_B_2);

    return ESP_OK;
}


// INTERNAL WRITE MOTOR A

esp_err_t d_m_drv8871_internal_write_motor_a_positive_mode_up(float duty)
{
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A));
    ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0));

    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_write_motor_a_negative_mode_up(float duty)
{
    // It recieve a negative value for the duty
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B));
    ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, -duty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0));
    
    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_write_motor_a_zero_mode_up(float duty)
{
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A));
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B));

    return ESP_OK;
}


// INTERNAL WRITE MOTOR B

esp_err_t d_m_drv8871_internal_write_motor_b_positive_mode_up(float duty)
{
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A));
    ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, duty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0));
    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_write_motor_b_negative_mode_up(float duty)
{
    // It recieve a negative value for the duty
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B));
    ESP_ERROR_CHECK(mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, -duty));
    ESP_ERROR_CHECK(mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0));
    return ESP_OK;
}

esp_err_t d_m_drv8871_internal_write_motor_b_zero_mode_up(float duty)
{
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A));
    ESP_ERROR_CHECK(mcpwm_set_signal_high(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B));
    return ESP_OK;
}
