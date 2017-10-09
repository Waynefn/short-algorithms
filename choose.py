def choose2(a):
    flag=0
    sum=[0,0]
    for i in range(len(a)):
        if a[i]>0:
            sum[int((flag&2)/2)]+=a[i]
            flag=int(2-flag&2)
        else:
            flag=0
    return max(sum)
