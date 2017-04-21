#!/usr/bin/env python3
"""
Generate a 128 bit UUID for use in NimBLE.
"""

import argparse
import uuid


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name", help="Variable name")

    return parser.parse_args()


def main():
    args = parse_args()

    u = uuid.uuid4()

    template = """
/* {uuid} */
ble_uuid128_t {name} =
    BLE_UUID128_INIT({uuid_bytes});
    """

    u_bytes = ", ".join("0x{:02x}".format(s) for s in u.bytes[::-1])
    print(template.format(uuid=u, uuid_bytes=u_bytes, name=args.name))


if __name__ == '__main__':
    main()
