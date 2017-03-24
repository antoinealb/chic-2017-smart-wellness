/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "os/os.h"
#include "bsp/bsp.h"
#include "hal/hal_gpio.h"
#include "hal/hal_i2c.h"
#include "mcu/stm32f4_bsp.h"
#include "mcu/stm32f4xx_mynewt_hal.h"
#include "veml6075-uv-sensor/veml6075-uv-sensor.h"

#ifdef ARCH_sim
#include "mcu/mcu_sim.h"
#endif

static volatile int g_task1_loops;

void sensor_transmit(void *i2c_dev,
                     uint8_t addr,
                     uint8_t *tx,
                     size_t tx_bytes,
                     uint8_t *rx,
                     size_t rx_bytes)
{
    struct hal_i2c_master_data rxdata = {.address = addr, .len = rx_bytes, .buffer = rx};
    struct hal_i2c_master_data txdata = {.address = addr, .len = tx_bytes, .buffer = tx};


    if (rx_bytes == 0) {
        hal_i2c_master_write((int)i2c_dev, &txdata, HAL_MAX_DELAY, 1);
    } else {
        hal_i2c_master_write((int)i2c_dev, &txdata, HAL_MAX_DELAY, 0);
        hal_i2c_master_read((int)i2c_dev, &rxdata, HAL_MAX_DELAY, 1);
    }
}

/* For LED toggling */
int g_led_pin;

/**
 * main
 *
 * The main task for the project. This function initializes packages,
 * and then blinks the BSP LED in a loop.
 *
 * @return int NOTE: this function should never return!
 */
int
main(int argc, char **argv)
{
    int rc;
    veml6075_dev_t sensor;

#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    sysinit();

    g_led_pin = LED_BLINK_PIN;
    hal_gpio_init_out(g_led_pin, 1);

    veml6075_init(&sensor, sensor_transmit, (void *)0);
    veml6075_configure(&sensor, VEML6075_TRIGGER_MANUAL, VEML6075_EXPOSURE_50MS, false);

    while (1) {
        ++g_task1_loops;

        /* Wait one second */
        os_time_delay(OS_TICKS_PER_SEC);

        /* Toggle the LED */
        hal_gpio_toggle(g_led_pin);

        rc = hal_i2c_master_probe(0, 0x20, OS_TICKS_PER_SEC);
        assert(rc == 0);
    }
    assert(0);

    return rc;
}
