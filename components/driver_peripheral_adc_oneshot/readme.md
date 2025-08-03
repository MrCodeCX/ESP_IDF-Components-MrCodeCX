DRIVER PERIPHERAL ADC ONESHOT

A COMPLETE EASY MANAGER FOR MULTIPLE ADC ONESHOTS LECTURES

This driver depends of esp_adc from the espressif oficial components

This driver is more stable than adc_continuous from espressif because, the adc_continuous works bad with 3 channels or more in esp32

This driver use global handles, the driver manages itself every handle realated to the adc units and handles
Then the user just have to call to the setup function with his own config of dp_adc_oneshot_cfg_t, and the driver will config and manage this

The user can have only one config per combination of adc unit and adc channels, if two configs have common channels in an adc unit, its an error

ADC 1 CHANNELS PER PIN
ADC1_CH0	GPIO 36
ADC1_CH1	GPIO 37
ADC1_CH2	GPIO 38
ADC1_CH3	GPIO 39
ADC1_CH4	GPIO 32
ADC1_CH5	GPIO 33
ADC1_CH6	GPIO 34
ADC1_CH7	GPIO 35


WORKFLOW API

// CONFIG
d_p_adc_oneshot_cfg_t adc_oneshot_config = {
    .adc_unit = ADC_UNIT_1,
    .n_channels = 3,
    .adc_channels = {ADC_CHANNELS_0, ADC_CHANNELS_1, ADC_CHANNEL_2}
}

// SETUP
d_p_adc_oneshot_setup(&adc_oneshot_config);

// READ
int lectures[3];
d_p_adc_oneshot_read(&adc_oneshot_config, lectures);

// KILL
d_p_adc_oneshot_kill(&adc_oneshot_config);