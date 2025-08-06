#include <d_s_distance_analog_conversions.h>
#include <math.h>


/**
 * GENERAL FUNCTION CONVERSIONS, provided by this driver, the user can use one of this functions or his own conversion function
 * THE DEFAULT FLAG FOR OUT OF RANGE AND DEAD ZONE IS -1
 */

// ------------------------------ SHARP GP2Y0A21 ------------------------------

float d_s_distance_analog_conversion_sharp_gp2y0a21(float voltage)
{
    float distance = -1;
    if(voltage > 0.4) distance = 27.5 * pow(voltage, -1.15);
    return distance;
}

// ------------------------------ RZ60S (DIGITAL) ------------------------------

float d_s_distance_analog_conversion_rz60s(float voltage)
{
    float distance = -1;
    if(voltage > D_P_ADC_ONESHOT_CHANNELS_VOLTAGE_MAX / 2) distance = 10;
    return distance;
}
