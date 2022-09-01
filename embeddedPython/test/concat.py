import sys
def concat(a,b):
    print(sys.version)
    # f-strings not supported until after 3.6
    print('got:' + ' ' + type(a).__name__ + ' ' + type(b).__name__)
    c = a + b
    print('Going to return:' + type(c).__name__)
    return c