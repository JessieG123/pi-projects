import time

import explorerhat as exh


blue = exh.light.blue
yellow = exh.light.yellow
green = exh.light.green
red = exh.light.red



def high(x):
    if (x >= 4.5):
        return True
    else:
        return False

def low(x):
    if (x <= 0.01):
        return True
    else:
        return False
    

def isButton(b):
    if (b == 1):
        return True
    return False



while True:
    #print(exh.input.one.read())
    #print(exh.analog.one.read())
    #print(exh.analog.two.read())
    
    x = exh.analog.one.read()
    y = exh.analog.two.read()
    button = exh.input.one.read()
    
    blue.off()
    red.off()
    yellow.off()
    green.off()
    
    if (high(x)):
        blue.on()  
    else:
        if (low(x)):
            red.on()
    
    if isButton(button):
        blue.on()
        red.on()
        yellow.on()
        green.on()
    
    if (high(y)):
        yellow.on()
    else:
        if (low(y)):
            green.on()
    
    
    time.sleep(0.01)