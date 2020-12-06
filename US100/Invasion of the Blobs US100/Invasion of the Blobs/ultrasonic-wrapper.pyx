cdef extern void initUltrasonic()
cdef extern void initTimer()
cdef extern void freeUltrasonic()
cdef extern void freeTimer()
cdef extern void txHigh()
cdef extern void txLow()
cdef extern int getTxLevel()
cdef extern int checkRxLevel()
cdef extern void clearTxRx()
cdef extern unsigned long long getSystemTimerCounter()

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
    
    def getTxLevel(self):
        return getTxLevel()
    
    def checkRxLevel(self):
        return checkRxLevel()

    def getSystemTimerCounter(self):
        return getSystemTimerCounter()
