# Notes on BLE

* https://punchthrough.com/bean/docs/guides/everything-else/how-gap-and-gatt-work/
* https://learn.adafruit.com/introduction-to-bluetooth-low-energy/gap
* https://punchthrough.com/blog/posts/developing-cross-platform-ble-apps-our-experience (their whole blog seems nice)
* http://doc.qt.io/qt-5/qtbluetooth-le-overview.html

Several layers:

##Generic Access Profile (GAP)

* Handles discovery, pairing etc... Seems similar to the "transport layer" in the TCP IP model
* Probably won't have to touch that one for now

## Generic ATTribute Profile

GATT describes in detail how attributes (data) are transferred once devices have a dedicated connection.

* exposes a set of services, each containing characteristics

for example the environmental service contains a UV index characteristic

Each service and characteristics has a 128 bit UUID.
Since it is a UUID, no need to ask for a standard, just generate one.
We can also shell out 2500 USD to have our own 16 bit, but why ?

Apparently its just a thin layer over the ATT

## ATTribute Protocol (ATT)

To quote the Qt docs:

> The basic building block of ATT is an attribute. Each attribute consists of three elements:
>
> * a value - the payload or desirable piece of information
> * a UUID - the type of attribute (used by GATT)
> * a 16-bit handle - a unique identifier for the attribute
> The server stores the attributes and the client uses the ATT protocol to read and write values on the server.

