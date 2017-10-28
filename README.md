# CHIC 2017 "Smart Wellness"

[![Build Status](http://178.32.216.117:8000/api/badges/antoinealb/chic-2017-smart-wellness/status.svg)](http://178.32.216.117:8000/antoinealb/chic-2017-smart-wellness)


## Building

1. Install Docker

This repository uses Docker for easy toolchain installation.
If you prefer, you can install the Apache Newt tool, as documented in the [Getting Started Guide](http://mynewt.apache.org/os/get_started/introduction/).

2. Download the dependencies

```no-highlight
    $ ./newt install
```

3. Build the blinky app for the sim platform using the "my_blinky_sim" target
(executed from the blinky directory).

```no-highlight
    $ ./newt build my_blinky_sim
```

The Apache Newt tool should indicate the location of the generated blinky executable.
Since the simulator does not have an LED to blink, this version of blinky is not terribly exciting - a printed message indicating the current LED state.

## Testing

This project's unit tests are not written in the conventional Mynewt fashion, but with Cpputest
They are built using CMake:

```bash
# Only needed once
mkdir -p build
cd build
cmake ..

# Build and runs tests
make check
```

# Connections on the BLE module

on the wire:

1. 3v3
2. gnd
3. sda
4. scl

on the module:

1. vin
2. gnd
3. P0.04
4. P0.05


## Patching OpenOCD for nrf52 support

First, clone the OpenOCD source code somewhere appropriate

    git clone git://git.code.sf.net/p/openocd/code openocd

Then you can build OpenOCD (change the prefix for your use case):

    ./bootstrap
    ./configure \
        --prefix=$HOME/custom-binaries/ \
        --program-prefix=nrf52- \
        --enable-aice \
        --enable-amtjtagaccel \
        --enable-armjtagew \
        --enable-cmsis-dap \
        --enable-dummy \
        --enable-ftdi \
        --enable-openjtag_ftdi \
        --enable-stlink

    make
    make install

OpenOCD git commit 41092636 was tested to be working.
