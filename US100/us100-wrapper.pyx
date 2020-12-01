cdef extern void initUs100()
cdef extern void freeUs100()
cdef extern void calculateDistance()    #TODO: Update this

#TODO: Double check
class us100Wrapper: 
	def __init__ (self):
		initUs100()
	
	def __del__(self):
		freeUs100()

    #TODO: do it similar like lights-wrapper example. LED_SET (Self, n) and LED_CLEAR(Self, n)
	def getDistance(self):
		return calculateDistance()
