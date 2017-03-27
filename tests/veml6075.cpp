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
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "veml6075-uv-sensor/veml6075-uv-sensor.h"

void i2c_mock_transmit(void *dev,
                       uint8_t addr,
                       uint8_t *tx,
                       size_t txbytes,
                       uint8_t *rx,
                       size_t rxbytes)
{
    (void) dev;
    (void) rxbytes;

    mock("i2c").actualCall("transmit")
    .withParameter("addr", addr)
    .withMemoryBufferParameter("tx", tx, txbytes)
    .withOutputParameter("rx", rx);
}

TEST_GROUP(I2CMock)
{
};

TEST(I2CMock, MockWorks)
{
    uint8_t data[] = {1, 2, 3};
    uint8_t rx_data[] = {1, 2, 3, 4};
    uint8_t rx[4];

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x42)
    .withMemoryBufferParameter("tx", data, sizeof(data))
    .withOutputParameterReturning("rx", rx_data, sizeof(rx_data));

    i2c_mock_transmit(NULL, 0x42, data, sizeof(data), rx, sizeof(rx));
}

TEST_GROUP(SunSensorDriver)
{
    veml6075_dev_t drv;
    int i2c_dev_dummy;

    void setup()
    {
        veml6075_init(&drv, i2c_mock_transmit, &i2c_dev_dummy);
    }
};

TEST(SunSensorDriver, CanInit)
{
    POINTERS_EQUAL(drv.i2c_dev,  &i2c_dev_dummy);
    POINTERS_EQUAL(drv.i2c_transmit,  &i2c_mock_transmit);
}

TEST(SunSensorDriver, CanConfigure)
{
    uint8_t data[] = {0, (1 << 1) | (1 << 3) | (2 << 4), 0};

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x10)
    .withMemoryBufferParameter("tx", data, sizeof(data))
    .withOutputParameterReturning("rx", NULL, 0);

    veml6075_configure(&drv, VEML6075_TRIGGER_MANUAL, VEML6075_EXPOSURE_200MS, true);
}

TEST(SunSensorDriver, CanReadUVA)
{
    uint8_t data[] = {0x07};
    uint8_t answer[] = {0x42, 0x12};

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x10)
    .withMemoryBufferParameter("tx", data, sizeof(data))
    .withOutputParameterReturning("rx", answer, sizeof(answer));

    uint16_t uva = veml6075_read_uva(&drv);

    CHECK_EQUAL(0x1242, uva);
}

TEST(SunSensorDriver, CanReadUVB)
{
    uint8_t data[] = {0x09};
    uint8_t answer[] = {0x42, 0x12};

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x10)
    .withMemoryBufferParameter("tx", data, sizeof(data))
    .withOutputParameterReturning("rx", answer, sizeof(answer));

    uint16_t uvb = veml6075_read_uvb(&drv);

    CHECK_EQUAL(0x1242, uvb);
}

TEST(SunSensorDriver, CanReadChipID)
{
    uint8_t request[] = {0x0C};
    uint8_t answer[] = {0x26, 0x00};

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x10)
    .withMemoryBufferParameter("tx", request, sizeof(request))
    .withOutputParameterReturning("rx", answer, sizeof(answer));

    uint16_t chip_id = veml6075_read_chip_id(&drv);

    CHECK_EQUAL(VEML6075_CHIP_ID, chip_id);
}
