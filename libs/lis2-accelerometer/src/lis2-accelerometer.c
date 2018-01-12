#include "lis2-accelerometer/lis2-accelerometer.h"

#define LIS2_ADDR 0x1e

#define LIS2_REG_WHO_AM_I 0x0f

void lis2_init(lis2_dev_t *dev, lis2_i2c_transmit_fn i2c_transmit, void *i2c_dev)
{
    dev->i2c_transmit = i2c_transmit;
    dev->i2c_dev = i2c_dev;
}

uint8_t lis2_read_chip_id(lis2_dev_t *dev)
{
    uint8_t reply[1];
    uint8_t msg[] = {LIS2_REG_WHO_AM_I};

    dev->i2c_transmit(dev->i2c_dev, LIS2_ADDR, msg, sizeof(msg), reply, sizeof(reply));

    return reply[0];
}
