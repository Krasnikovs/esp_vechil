import serial
import numpy as np

class ReadSerial():
    def __init__(self):
        self.serial_port = self.detect_serial_port()

    def detect_serial_port(self):
        serial_port_number = 0
        serial_port = f'/dev/ttyACM{serial_port_number}'

        serail_set = False

        while serail_set == False:
            try:
                serial.Serial(serial_port)
                serail_set = True
            except:
                serial_port_number +=1
                serial_port = f'/dev/ttyACM{serial_port_number}'

        return serial_port
    
    def read_serial(self):
        try: 
            with serial.Serial(self.serial_port, 115200, timeout = 1) as ser:
                read_ser = ser.readline()
                vechicle_estimate = np.array([read_ser.QX, read_ser.QY, read_ser.QX, read_ser.QW, read_ser.AX, read_ser.AY, read_ser.AZ])
                print(read_ser)
                return read_ser
        except:
            print('No board')
