cdef extern void initUs100()
cdef extern void freeUs100()
cdef extern void calculateDistance()

#TODO: Double check
class us100Wrapper: 
	def __init__ (self):
		initUs100()
	
	def __del__(self):
		freeUs100()

	def getDistance(self):
		return calculateDistance()
