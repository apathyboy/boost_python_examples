
from TEST1 import DelayedCallback

def SomeFunc():
    print("Delayed Function");


print("Command 1 start")

return DelayedCallback(SomeFunc, 5000.0)
