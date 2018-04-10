#!/bin/usr/env python

import serial
import sys
import time


def main():
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=30)
    time.sleep(2)
    nBlinks = str(sys.argv[1])
    # print(nBlinks.encode())
    result = ser.write(nBlinks.encode())
    # print(result)
    if (result):
        print("SENT "+ nBlinks + " TO DEVICE")
    else:
        print("ERROR")
    line = ser.readline()
    print(line)
    ser.close()


if __name__ == "__main__":
    main()
