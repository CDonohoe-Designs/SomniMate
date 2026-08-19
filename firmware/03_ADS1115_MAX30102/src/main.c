/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * Combined I2C bring-up test for the ADS1115 and MAX30102.
 * Confirms that both devices can operate on the same I2C bus
 * using separate device addresses.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - ADS1115 ADC
 * - MAX30102 optical sensor
 *
 * Framework:
 * - Zephyr RTOS
 * - nRF Connect SDK
 */
#include <stdio.h>
#include <stdint.h>
#include <zephyr/drivers/i2c.h>

int main(void)
{
    uint8_t max30102_address = 0x57;
    uint8_t max30102_part_id_reg = 0xFF;
    uint8_t max30102_part_id;

    uint8_t ads1115_address = 0x48;
    uint8_t ads1115_config_reg = 0x01;
    uint8_t ads1115_conf_bytes[2];

    const struct device *i2c_dev =
        DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));

    printf("Board: %s\n", CONFIG_BOARD_TARGET);

    if (!device_is_ready(i2c_dev))
    {
        printf("I2C device is not ready\n");
        return -1;
    }

    printf("I2C device is ready\n\n");


    ////////////////////////* MAX30102 *//////////////////////////

    printf("MAX30102 address: 0x%x\n", max30102_address);

    int result_MAX30102 = i2c_write_read(
        i2c_dev,
        max30102_address,
        &max30102_part_id_reg,
        1,
        &max30102_part_id,
        1);

    printf("MAX30102 I2C result: %d\n", result_MAX30102);

    if (result_MAX30102 < 0)
    {
        printf("MAX30102 read not successful, error = %d\n",
               result_MAX30102);
        return -1;
    }

    printf("MAX30102 Part ID: 0x%x\n", max30102_part_id);

    if (max30102_part_id == 0x15)
    {
        printf("MAX30102 detected\n");
    }


    printf("\n");


    //////////////////////////* ADS1115 */////////////////////////

    printf("ADS1115 address: 0x%x\n", ads1115_address);

    int result_ADS1115 = i2c_write_read(
        i2c_dev,
        ads1115_address,
        &ads1115_config_reg,
        1,
        ads1115_conf_bytes,
        2);

    printf("ADS1115 I2C result: %d\n", result_ADS1115);

    if (result_ADS1115 < 0)
    {
        printf("ADS1115 read not successful, error = %d\n",
               result_ADS1115);
        return -1;
    }

    printf("ADS1115 Config: 0x%x%x\n",
           ads1115_conf_bytes[0],
           ads1115_conf_bytes[1]);

    if ((ads1115_conf_bytes[0] == 0x85) &&
        (ads1115_conf_bytes[1] == 0x83))
    {
        printf("ADS1115 detected\n");
    }

    return 0;
    
}
