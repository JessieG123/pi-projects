# 03-analog-in.py - analog input demo
import explorerhat as exh
import time

analogInx = exh.analog[0]
analogIny = exh.analog[1]

xLast = analogInx.read()
yLast = analogIny.read()
#light = exh.light[1]

pushButton = exh.input[0]
lastState = pushButton.read()

while True :
    state = pushButton.read()
    x = analogInx.read()
    y = analogIny.read()
    if state != lastState:
        print( "state of button:", state)
        lastState = state
    if x != xLast:
        print("x:", x)
        xLast = x
    if y != yLast:
        print("y:", y)
        yLast = y
#    if abs(x - xLast) > 0.1 :
#        xLast = x
#        print( x )
#    light.brightness( max( 0, min( 100, 100 * x / 5 ) ) )
    time.sleep( 0.1 ) # 50Hz (if frequency is too low, LED flickers)
    
