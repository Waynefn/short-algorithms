# a demo to achieve dynamic get_xxx and set_xxx methods
from functools import partial

class Params(object):
    def __getattribute__(self,p):
        s=p.split("_")
        if s[0]=="get":
            return lambda:object.__getattribute__(self,s[1])
        if s[0]=="set":
            return partial(Params.__setattr__, self, s[1])
        return object.__getattribute__(self,p)
    
a=Params()
a.pi=3.14
a.pi # return 3.14
a.get_pi() # return a.pi
a.set_pi(5) # a.pi=5
