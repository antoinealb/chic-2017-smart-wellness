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
