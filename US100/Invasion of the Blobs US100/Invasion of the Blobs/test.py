import ultrasonic
import time

u = ultrasonic.Ultrasonic()


def pulseTx(u):
    
    print("AFTER txHigh:" + str(u.getTxLevel()))
    
    
    
    
    

while True:
    print("BEFORE txHigh:" + str(u.getTxLevel()))
    u.txHigh()
    time.sleep(0.0001) #wait 100us
    print("BEFORE txLow:" + str(u.getTxLevel()))
    u.txLow()
    print("AFTER tcLow:" + str(u.getTxLevel()))

    # Wait for Rx pin to go high
    print("rx level 1: " + str(u.checkRxLevel()))
    
    while (u.checkRxLevel() == 0):
        time.sleep(0.000001)
    t1 = u.getSystemTimerCounter() / 1000000
    print("t1: " + str(t1) + "\n")
    
    print("rx level 2: " + str(u.checkRxLevel()))
    while (u.checkRxLevel() == 1):
        time.sleep(0.000001)
    t2 = u.getSystemTimerCounter() /1000000
    print("t2: " + str(t2) + "\n")
    timePeriod = (t2 - t1) #seconds
    
    print("timePeriod: " + str(timePeriod))
    
    distance = 0.5 * timePeriod * 34300
    print("distance: " + str(distance))
    
