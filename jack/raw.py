# Copyright 2024 jack@pngu.org
# SPDX-License-Identifier: GPL-2.0-or-later
import hid
import sys
import psutil
import math
import time
import datetime

vendor_id = 0x6A73
product_id = 0x6B62
usage_page = 0xFF60
usage = 0x61


def get_raw_hid_interface():
    device_interfaces = hid.enumerate(vendor_id, product_id)
    raw_hid_interfaces = [
        i
        for i in device_interfaces
        if i["usage_page"] == usage_page and i["usage"] == usage
    ]
    if len(raw_hid_interfaces) == 0:
        return None
    interface = hid.Device(path=raw_hid_interfaces[0]["path"])
    return interface


def send_packet(data):
    interface = get_raw_hid_interface()
    if interface is None:
        print("no device found")
        sys.exit(1)
    request_data = [0x00] * 32
    request_data[1 : len(data) + 1] = data
    request_packet = bytes(request_data)
    try:
        interface.write(request_packet)
    finally:
        interface.close()


if __name__ == "__main__":
    while True:
        time.sleep(30)
        cpu_temp = psutil.sensors_temperatures()["gigabyte_wmi"][2]
        cur_hour = datetime.datetime.now().strftime("%H")
        cur_minute = datetime.datetime.now().strftime("%M")
        send_packet([math.trunc(cpu_temp.current), int(cur_hour), int(cur_minute)])
