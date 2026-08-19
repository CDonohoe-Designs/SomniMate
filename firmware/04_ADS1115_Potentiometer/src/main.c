/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * ADS1115 analogue-input test using a potentiometer on AIN3.
 * Configures the ADC for single-ended AIN3-to-GND conversion,
 * reads the conversion register and converts the result to volts.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - ADS1115 ADC
 * - Potentiometer connected to AIN3
 *
 * Framework:
 * - Zephyr RTOS
 * - nRF Connect SDK
 */
#include <stdio.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>

int main(void)
{
    uint8_t ads1115_address = 0x48;

    /*
     * ADS1115 config = 0xF383
     * AIN3-to-GND, +/-4.096 V range, single-shot mode,
     * 128 SPS, comparator disabled.
     */
    uint8_t ads1115_config_write[3];

    ads1115_config_write[0] = 0x01;
    ads1115_config_write[1] = 0xF3;
    ads1115_config_write[2] = 0x83;

    uint8_t ads1115_conversion_reg = 0x00;
    uint8_t ads1115_conversion_bytes[2];
    int16_t adc_value;

    const struct device *i2c_dev =
        DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));

    printf("ADS1115 Address: 0x%x\n", ads1115_address);
    printf("Board: %s\n", CONFIG_BOARD_TARGET);

    if (!device_is_ready(i2c_dev))
    {
        printf("I2C device is not ready\n");
        return -1;
    }

    printf("I2C device is ready\n");

    while (1)
    {
        /* Start single-shot conversion */
        i2c_write(
            i2c_dev,
            ads1115_config_write,
            3,
            ads1115_address);

        /* Allow conversion to complete */
        k_msleep(10);

        /* Read conversion register */
        i2c_write_read(
            i2c_dev,
            ads1115_address,
            &ads1115_conversion_reg,
            1,
            ads1115_conversion_bytes,
            2);

        /* Combine MSB and LSB into 16-bit ADC value */
        adc_value =
            (int16_t)((ads1115_conversion_bytes[0] << 8) |
                      ads1115_conversion_bytes[1]);

        /* +/-4.096 V range = 125 uV per ADC count */
        double voltage = adc_value * 0.000125;

        printf("ADC voltage = %.3f V\n", voltage);

        k_msleep(250);
    }

    return 0;
}
