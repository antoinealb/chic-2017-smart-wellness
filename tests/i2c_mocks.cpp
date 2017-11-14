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
#include "i2c_mocks.hpp"

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
