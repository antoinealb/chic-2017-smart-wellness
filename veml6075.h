#ifndef VEML6075_H
#define VEML6075_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef void (*veml7075_i2c_transmit_fn)(void *dev, uint8_t addr, const uint8_t *tx, size_t txbytes,
                                         uint8_t *rx, size_t rxbytes);

typedef struct {
    void *i2c_dev;
    veml7075_i2c_transmit_fn i2c_transmit;
} veml6075_dev_t;

void veml6075_init(veml6075_dev_t *dev, veml7075_i2c_transmit_fn i2c_transmit, void *i2c_dev);

#ifdef __cplusplus
}
#endif

#endif
