#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "bsp/bsp.h"
#include "host/ble_hs.h"
#include "host/ble_uuid.h"
#include "bleprph.h"

/**
 * The vendor specific sensor test has the following characteristics:
 *
 * * Chip ID read: This characteristic reads the chip id of the veml 6075 chip.
 */

/* 11a8564d-e4a9-4bc8-8775-140c25d30783 */
static const ble_uuid128_t gatt_svr_svc_sensor_test_uuid =
    BLE_UUID128_INIT(0x83, 0x07, 0xd3, 0x25, 0x0c, 0x14, 0x75, 0x87,
                     0xc8, 0x4b, 0xa9, 0xe4, 0x4d, 0x56, 0xa8, 0x11);

/* 0b08ccd6-27a1-4439-98b4-36878efafd7a */
static const ble_uuid128_t gatt_svr_svc_sensor_test_chipid_uuid =
    BLE_UUID128_INIT(0x7a, 0xfd, 0xfa, 0x8e, 0x87, 0x36, 0xb4, 0x98, 0x39, 0x44, 0xa1, 0x27, 0xd6, 0xcc, 0x08, 0x0b);



static int gatt_svr_chr_access_sensor_test_chipd(uint16_t conn_handle, uint16_t attr_handle, struct ble_gatt_access_ctxt *ctxt, void *arg)
{
    int rc;

    /* TODO: Read chip id instead. */
    uint32_t chipid = 42;


    rc = os_mbuf_append(ctxt->om, &chipid, sizeof chipid);
    return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
}

static const struct ble_gatt_svc_def gatt_svr_svcs[] = {
    {
        /*** Service: Sensor test. */
        .type = BLE_GATT_SVC_TYPE_PRIMARY,
        .uuid = &gatt_svr_svc_sensor_test_uuid.u,
        .characteristics = (struct ble_gatt_chr_def[]) {
            {
                /*** Characteristic: Chip ID. */
                .uuid = &gatt_svr_svc_sensor_test_chipid_uuid.u,
                .access_cb = gatt_svr_chr_access_sensor_test_chipd,
                .flags = BLE_GATT_CHR_F_READ,
            }, {
                0, /* No more characteristics in this service. */
            }
        },
    },

    {
        0,         /* No more services. */
    },
};

int
gatt_svr_init(void)
{
    int rc;

    rc = ble_gatts_count_cfg(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    rc = ble_gatts_add_svcs(gatt_svr_svcs);
    if (rc != 0) {
        return rc;
    }

    return 0;
}
