#include <string.h>
#include "veml6075.h"

void veml6075_init(veml6075_dev_t *dev, veml7075_i2c_transmit_fn transmit_fn, void *i2c_dev)
{
    memset(dev, 0, sizeof(veml6075_dev_t));
    dev->i2c_dev = i2c_dev;
    dev->i2c_transmit = transmit_fn;
}
