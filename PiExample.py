import explorerhat as exh
import time

red = exh.light.red
yellow = exh.light.yellow
green = exh.light.green
blue = exh.light.blue


while True:
	red.on()
	time.sleep(0.25)
	red.off()
	yellow.on()
	time.sleep(0.25)
	yellow.off()
	green.on()
	time.sleep(0.25)
	green.off()
	blue.on()
	time.sleep(0.25)
	blue.off()
	red.on()
	yellow.on()
	green.on()
	blue.on()
	time.sleep(0.25)
	red.off()
	yellow.off()
	green.off()
	blue.off()