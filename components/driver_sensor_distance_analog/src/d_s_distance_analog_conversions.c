#include <d_s_distance_analog_conversions.h>
#include <math.h>

float d_s_convert_distance_sharp_gp2y0a21(float voltage)
{
    float distance = -1;
    if(voltage > 0.4) distance = 27.5 * pow(voltage, -1.15);
    return distance;
}

float d_s_convert_distance_digital_rz60s(float voltage)
{
    float distance = -1;
    if(voltage > D_P_ADC_ONESHOT_CHANNELS_VOLTAGE_MAX / 2) distance = 10;
    return distance;
}
