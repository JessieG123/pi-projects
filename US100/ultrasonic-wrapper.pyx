cdef extern void initUltrasonic()
cdef extern void freeUltrasonic()
cdef extern void txHigh()
cdef extern void txLow()
cdef extern void checkRxLevel()
cdef extern void clearTxRx()

#TODO: Double check
class Ultrasonic: 
    def __init__ (self):
        initUltrasonic()
    
    def __del__(self):
        clearTxRx()
        freeUltrasonic()

    def txHigh(self):
        return txHigh()
    
    def txLow(self):
        return txLow()
    
    def checkRxLevel(self):
        return checkRxLevel()
