#ifndef I2C_MOCKS_HPP
#define I2C_MOCKS_HPP

#include <cstdint>
#include <cstdlib>

void i2c_mock_transmit(void *dev,
                       uint8_t addr,
                       uint8_t *tx,
                       size_t txbytes,
                       uint8_t *rx,
                       size_t rxbytes);



#endif
