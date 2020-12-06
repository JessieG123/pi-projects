import ultrasonic
import time

u = ultrasonic.Ultrasonic()


def pulseTx(u):
    print("BEFRE txHigh:" + str(u.getTxLevel()))
    u.txHigh()
    print("AFTER txHigh:" + str(u.getTxLevel()))
    time.sleep(0.0001) #wait 100us
    print("BEFRE txLow:" + str(u.getTxLevel()))
    u.txLow()
    print("AFTER tcLow:" + str(u.getTxLevel()))
    

while True:
    pulseTx(u)