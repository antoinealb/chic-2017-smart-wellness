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
#include <assert.h>
#include <string.h>

#include <sysinit/sysinit.h>
#include <os/os.h>
#include <bsp/bsp.h>
#include <hal/hal_gpio.h>

#ifdef ARCH_sim
#include <mcu/mcu_sim.h>
#endif

int main(int argc, char **argv)
{
#ifdef ARCH_sim
    mcu_sim_parse_args(argc, argv);
#endif

    sysinit();

    hal_gpio_init_out(LED_BLINK_PIN, 1);

    while (1) {
        /* Wait half a second */
        os_time_delay(OS_TICKS_PER_SEC / 2);

        /* Toggle the LED */
        hal_gpio_toggle(LED_BLINK_PIN);
    }

    /* Should never reach there. */
    assert(0);
    return 0;
}
