import ultrasonic
import time

u = ultrasonic.Ultrasonic()


def pulseTx(u):
    
    print("AFTER txHigh:" + str(u.getTxLevel()))
    
    
    
    
    

while True:
    print("BEFORE txHigh:" + str(bin(u.getTxLevel())))
    u.txHigh()
    time.sleep(0.0001) #wait 100us
    print("BEFORE txLow:" + str(u.getTxLevel()))
    u.txLow()
    print("AFTER tcLow:" + str(u.getTxLevel()))