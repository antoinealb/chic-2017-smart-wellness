/*
 * Copyright 2017 Antoine Albertelli <antoine@antoinealb.net>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <string.h>
#include "veml6075-uv-sensor/veml6075-uv-sensor.h"

#define VEML6075_ADDR 0x10

#define VEML6075_CMD_CONF 0x00
#define VEML6075_CMD_UVA  0x07
#define VEML6075_CMD_UVB  0x09
#define VEML6075_CMD_ID   0x0C


void veml6075_init(veml6075_dev_t *dev, veml6075_i2c_transmit_fn transmit_fn, void *i2c_dev)
{
    memset(dev, 0, sizeof(veml6075_dev_t));
    dev->i2c_dev = i2c_dev;
    dev->i2c_transmit = transmit_fn;
}

void veml6075_configure(veml6075_dev_t *dev,
                        enum veml6075_trigger_mode trigger,
                        enum veml6075_integration_time it,
                        bool use_high_dynamic)
{
    uint16_t config = 0;

    config |= trigger << 1;
    config |= it << 4;

    if (use_high_dynamic) {
        config |= (1 << 3);
    }

    uint8_t msg[] = {VEML6075_CMD_CONF, config & 0xff, config >> 8};

    dev->i2c_transmit(dev->i2c_dev, VEML6075_ADDR, msg, sizeof(msg), NULL, 0);
}

uint16_t veml6075_read_uva(veml6075_dev_t *dev)
{
    uint8_t msg[] = {VEML6075_CMD_UVA};
    uint8_t value[2];
    dev->i2c_transmit(dev->i2c_dev, VEML6075_ADDR, msg, sizeof(msg), value, sizeof(value));

    return (value[1] << 8) + value[0];
}

uint16_t veml6075_read_uvb(veml6075_dev_t *dev)
{
    uint8_t msg[] = {VEML6075_CMD_UVB};
    uint8_t value[2];
    dev->i2c_transmit(dev->i2c_dev, VEML6075_ADDR, msg, sizeof(msg), value, sizeof(value));

    return (value[1] << 8) + value[0];
}

uint16_t veml6075_read_chip_id(veml6075_dev_t *dev)
{
    uint8_t msg[] = {VEML6075_CMD_ID};
    uint8_t value[2];
    dev->i2c_transmit(dev->i2c_dev, VEML6075_ADDR, msg, sizeof(msg), value, sizeof(value));

    return (value[1] << 8) + value[0];

}
