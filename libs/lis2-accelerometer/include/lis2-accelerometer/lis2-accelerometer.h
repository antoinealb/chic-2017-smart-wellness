#ifndef LIS2_ACCELEROMETER_H
#define LIS2_ACCELEROMETER_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIS2_CHIP_ID 0x41


typedef void (*lis2_i2c_transmit_fn)(void *dev, uint8_t addr, uint8_t *tx, size_t txbytes,
                                         uint8_t *rx, size_t rxbytes);

typedef struct {
    void *i2c_dev;
    lis2_i2c_transmit_fn i2c_transmit;
} lis2_dev_t;


void lis2_init(lis2_dev_t *dev, lis2_i2c_transmit_fn i2c_transmit, void *i2c_dev);
uint8_t lis2_read_chip_id(lis2_dev_t *dev);


#ifdef __cplusplus
}
#endif

#endif
