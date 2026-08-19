/*
 * Project: nRF5340 Zephyr Sensor Bring-Up
 * File: main.c
 * Author: Caoilte Donohoe
 *
 * Purpose:
 * Combined I2C bring-up test for the ADS1115, MAX30102 and BH1750.
 * Confirms that all three devices can operate on the same I2C bus
 * using separate device addresses.
 *
 * Hardware:
 * - Nordic nRF5340 DK
 * - ADS1115 ADC
 * - MAX30102 optical sensor
 * - GY-302 / BH1750 ambient-light sensor
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
    uint8_t max30102_address = 0x57;
    uint8_t max30102_part_id_reg = 0xFF;
    uint8_t max30102_part_id;

    uint8_t ads1115_address = 0x48;
    uint8_t ads1115_config_reg = 0x01;
    uint8_t ads1115_conf_bytes[2];

    uint8_t bh1750_address = 0x23;
    uint8_t bh1750_mode = 0x10;
    uint8_t bh1750_data[2];
    uint16_t raw_light;
    uint32_t lux_x10;

    const struct device *i2c_dev =
        DEVICE_DT_GET(DT_NODELABEL(arduino_i2c));

    printf("Board: %s\n", CONFIG_BOARD_TARGET);

    if (!device_is_ready(i2c_dev))
    {
        printf("I2C device is not ready\n");
        return -1;
    }

    printf("I2C device is ready\n\n");

    /* BH1750 */
    i2c_write(
        i2c_dev,
        &bh1750_mode,
        1,
        bh1750_address);

    printf("BH1750 initialized\n");

    k_msleep(180);

    i2c_read(
        i2c_dev,
        bh1750_data,
        2,
        bh1750_address);

    raw_light =
        (bh1750_data[0] << 8) |
         bh1750_data[1];

    lux_x10 = ((uint32_t)raw_light * 10) / 12;

    printf("BH1750 Light = %u.%u lux\n",
           lux_x10 / 10,
           lux_x10 % 10);

    /* MAX30102 */
    printf("MAX30102 address: 0x%x\n", max30102_address);

    int result_MAX30102 = i2c_write_read(
        i2c_dev,
        max30102_address,
        &max30102_part_id_reg,
        1,
        &max30102_part_id,
        1);

    printf("MAX30102 I2C result: %d\n", result_MAX30102);
    printf("MAX30102 Part ID: 0x%x\n", max30102_part_id);

    if (max30102_part_id == 0x15)
    {
        printf("MAX30102 detected\n");
    }

    printf("\n");

    /* ADS1115 */
    printf("ADS1115 address: 0x%x\n", ads1115_address);

    int result_ADS1115 = i2c_write_read(
        i2c_dev,
        ads1115_address,
        &ads1115_config_reg,
        1,
        ads1115_conf_bytes,
        2);

    printf("ADS1115 I2C result: %d\n", result_ADS1115);

    printf("ADS1115 Config: 0x%02x%02x\n",
           ads1115_conf_bytes[0],
           ads1115_conf_bytes[1]);

    return 0;
}
