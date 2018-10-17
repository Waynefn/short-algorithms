#get English expression of a number
import math

wordList0_9=['','one','two','three','four','five','six','seven','eight','nine','ten']
wordList10_19=['','eleven','twelve','thirteen','fourteen','fifteen','sixteen','seventeen','eighteen','nineteen']
wordList10_90=['','ten','twenty','thirty','forty','fifty','sixty','seventy','eighty','ninety']
wordList100={0:'',3:'thousand',6:'million',9:'billion',12:'trillion'}

def engNum(numstr):
    numval=int(numstr)
    hundred,tens='',''
    if numval>=100 and numval<1000:
        hundred="%s hundred"%(wordList0_9[int(numstr[0])])
    tens="%s %s"%(wordList10_90[int(numstr[1])],wordList0_9[int(numstr[2])]) if numstr[2]!='0' else "%s"%(wordList10_90[int(numstr[1])])
    if numval%100<20 and numval%100>10:
        tens="%s"%(wordList10_19[int(numstr[2])])
    if numval%100<10:
        tens=wordList0_9[int(numstr[2])]
    return "%s %s"%(hundred,tens)


def integer(number):
    number=str(number)
    length=len(number)
    engW=''
    num=0
    for i in range(0,len(number)):
        num=num*10+int(number[i])
        if (length-i-1) in  wordList100.keys():
            if num>0:
                engW+=engNum('%03d'%num)
                engW+=" %s "%wordList100[length-i-1]
            num=0
    engW=engW.split()
    return ' '.join(engW).capitalize()

def small(number):
    s=''
    for i in number:
        if i=='0':
            s+='zero '
        else:
            s+=wordList0_9[int(i)]+' '
    return " point "+s.strip()



def main(s):
    spt=s.split('.')
    if len(spt)==1 and spt[0].isdigit():
        if spt[0]=='0':
            print('Zero')
        else:
            print(integer(spt[0]))
    elif len(spt)==2 and spt[0].isdigit() and  spt[1].isdigit():
        if spt[0]=='0':
            print('Zero',end='')
        else:
            print(integer(spt[0]),end='')
        print(small(spt[1]))
    else:
        return 1
    return 0
    

