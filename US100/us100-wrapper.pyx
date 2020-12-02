cdef extern void initUs100()
cdef extern void freeUs100()
cdef extern void txHigh()
cdef extern void txLow()
cdef extern void checkRxLevel()

#TODO: Double check
class us100Wrapper: 
	def __init__ (self):
		initUs100()
	
	def __del__(self):
		freeUs100()

	def txHigh(self):
		return txHigh()
    
    def txLow(self):
		return txLow()
    
    def checkRxLevel(self):
		return checkRxLevel()
