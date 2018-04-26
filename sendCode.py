#!/bin/usr/env python

import serial
import sys
import time


def main():
    ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=30, dsrdtr=False)
    time.sleep(2)
    nBlinks = str(sys.argv[1])
    # print(nBlinks.encode())
    result = ser.write(nBlinks.encode())
    # print(result)
    line = ser.readline()
    print(line)
    ser.close()


if __name__ == "__main__":
    main()
