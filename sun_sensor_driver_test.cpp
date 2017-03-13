#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>
#include "veml6075.h"

void i2c_mock_transmit(void *dev,
                       uint8_t addr,
                       const uint8_t *tx,
                       size_t txbytes,
                       uint8_t *rx,
                       size_t rxbytes)
{

}

TEST_GROUP(SunSensorDriver)
{
    veml6075_dev_t drv;
};

TEST(SunSensorDriver, CanInit)
{
    int i2c;
    veml6075_init(&drv, i2c_mock_transmit, &i2c);
    POINTERS_EQUAL(drv.i2c_dev,  &i2c);
    POINTERS_EQUAL(drv.i2c_transmit,  &i2c_mock_transmit);
}
