DRIVER SENSOR DISTANCE ANALOG

A SIMPLE API FOR MANAGE MULTIPLE SENSORS DISTANCE WITH ANALOG OUTPUT

This driver depends of the driver_peripheral_adc_oneshot from MrCodeCX components

The default flag for out of range and dead zone lectures is -1

The user can override the D_S_DISTANCE_ANALOG_VOLTAGE_TO_DISTANCE macro to use othe conversion function from d_s_distance_analog_conversions, or his own conversion function

The user can override the global object d_s_distance_analog_adc_oneshot_config during execution to create a new sensor config, but first have to kill the previous config if that previous config has been setup

To config edit the d_s_distance_analog_config.h and d_s_distance_analog_config.c files
All the config is needed

WORKFLOW API

// SETUP
d_s_distance_analog_setup()

// READ DISTANCES
float distances [D_S_DISTANCE_ANALOG_N_SENSORS];
esp_err_t d_s_distance_analog_read_distances(float *distances);

// KILL
d_s_distance_analog_kill();