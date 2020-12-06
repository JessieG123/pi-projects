cdef extern void initUltrasonic()
cdef extern void initTimer()
cdef extern void freeUltrasonic()
cdef extern void freeTimer()
cdef extern void txHigh()
cdef extern void txLow()
cdef extern void checkRxLevel()
cdef extern void clearTxRx()
cdef extern void getSystemTimerCounter()

#TODO: Double check
class Ultrasonic: 
    def __init__ (self):
        initUltrasonic()
        initTimer()
    
    def __del__(self):
        clearTxRx()
        freeUltrasonic()
        freeTimer()

    def txHigh(self):
        return txHigh()
    
    def txLow(self):
        return txLow()
    
    def checkRxLevel(self):
        return checkRxLevel()

    def getSystemTimerCounter():
        return getSystemTimerCounter()