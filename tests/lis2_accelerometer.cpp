#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "i2c_mocks.hpp"
#include "lis2-accelerometer/lis2-accelerometer.h"

TEST_GROUP(AccelerometerDriver)
{
    lis2_dev_t drv;
    int i2c_dev_dummy;

    void setup()
    {
        lis2_init(&drv, i2c_mock_transmit, &i2c_dev_dummy);
    }

};

TEST(AccelerometerDriver, CanInit)
{
    POINTERS_EQUAL(drv.i2c_dev,  &i2c_dev_dummy);
    POINTERS_EQUAL(drv.i2c_transmit,  &i2c_mock_transmit);
}

TEST(AccelerometerDriver, CanReadChipID)
{
    uint8_t request[1] = {0xf};
    uint8_t response[1] = {0x41};

    mock("i2c").expectOneCall("transmit")
    .withParameter("addr", 0x1e)
    .withMemoryBufferParameter("tx", request, sizeof(request))
    .withOutputParameterReturning("rx", response, sizeof(response));

    auto id = lis2_read_chip_id(&drv);
    CHECK_EQUAL(LIS2_CHIP_ID, id);
}
