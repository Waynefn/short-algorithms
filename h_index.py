# this is a method with O(n*log n) complexity
def hindex(citel):  
    citel.sort()# O(n*log n)
    h=1 if citel[-1]>0 else 0  
    small=citel[-1]  
    for i in citel[-2::-1]:  
        if i==small and i >h:  
            h+=1  
        elif i>h:  
            h+=1  
            small=i  
        else:  
            break  
    return h  
