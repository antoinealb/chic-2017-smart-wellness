# CHIC 2017 "Smart Wellness"

## Building

This repo contains an example Apache Mynewt application called blinky.
When executed on suitably equipped hardware, this application repeatedly blinks an LED.
The below procedure describes how to build this application for the Apache Mynewt simulator.

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
