def overHalf(a):
    h=a[0]
    count=1
    for i in range(1,len(a)):
        if h==a[i]:
            count+=1
        else:
            count-=1
        if count==0:
            h=a[i]
            count=1
    count=0
    for i in a:
        if i==h:
            count+=1
    return h if count>len(a)/2 else None
