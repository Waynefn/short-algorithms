import re
Selected=[0]*4
poExprist=[]
TupleList=[]
Operation=['+','-','*','/']

TotalList=[]

def reSimplify(li):
    global TotalList
    li= re.subn(r"\((.*?)\)",r"\1",li)[0]
    li= re.subn(r"\((\d+)([+*])\((.*?)\)\)",r"((\3)\2\1)",li)[0]
    li= re.subn(r"\(\((\d+)([+-])(\d+)\)([+-])(\d+)\)",r"(\1\2\3\4\5)",li)[0]
    li= re.subn(r"\(\((\d+)([*/])(\d+)\)([*/+-])(\d+)\)",r"(\1\2\3\4\5)",li)[0]
    li= re.subn(r"\(\((\d+)([+-])(\d+)\)([+-])(\d+)\)",r"(\1\2\3\4\5)",li)[0]
    li= re.subn(r"\((\d+)([+-])\((\d+)([*/])(\d+)\)\)",r"(\1\2\3\4\5)",li)[0]
    cnt=[0]*len(Operation)
    for i in li:
        if i in Operation:
            cnt[Operation.index(i)]+=1
    if cnt in TotalList:
        return ""
    else:
        #print(TotalList)
        TotalList.append(cnt)
        return li

def polish2Normal(li):
    stack=[]
    if len(li)==0:
        return ""
    for i in li:
        if i not in Operation:
            stack.append(i)
        else:
            n2=stack.pop()
            n1=stack.pop()
            stack.append("(%s)%s(%s)"%(str(n1),i,str(n2)))
    #print(stack[0])
    ret=reSimplify(stack[0])
    if ret !="":
        print( ret)

def calPoland(li):
    if li[-1]not in Operation:
        raise Exception("err")
    stack=[]
    for i in li:
        if i not in Operation:
            stack.append(i)
        else:
            n2=float(stack.pop())
            n1=stack.pop()
            try:
                stack.append(eval("%f%s%f"%(n1,i,n2)))
            except:
                return []
    return stack


def search24(visited, figCnt,opCnt,wholeEqu,poExpr):
    #print("in:",visited, figCnt,opCnt,wholeEqu,poExpr)
    if figCnt==4 and opCnt==3:
        if poExpr[0]<24.1 and poExpr[0]>23.9:
            polish2Normal(wholeEqu)
            #print(wholeEqu)
            return 
        else:
            return
    if figCnt>opCnt+1 and opCnt<3:
        cutList1=[]
        for i in Operation:
            nl=poExpr+[i]
            #print("out1",visited,figCnt,opCnt+1,i,nl)
            nl=calPoland(nl)
            if nl==[] or nl in cutList1:
                continue
            cutList1.append(nl)
            search24(visited,figCnt,opCnt+1,wholeEqu+[i],nl)
    if figCnt<4:
        cutList2=[]
        for j in range(0,4):
            if visited[j]==0 and poExprist[j] not in cutList2:
                cutList2.append(poExprist[j] )
                nl=poExpr+[poExprist[j]]
                visited[j]=1
                #print("out2",visited,figCnt+1,opCnt,j,nl)
                search24(visited,figCnt+1,opCnt,wholeEqu+[poExprist[j]],nl)
                visited[j]=0

def chooseTwo():
    global Selected,poExprist,TupleList
    for i  in range(0,4):
        Selected[i]=1
        for j in range(0,4):
            if Selected[j]==0:
                tup=[i,j]
                num=[poExprist[i],poExprist[j]]
                if num not in TupleList:
                    Selected[j]=1
                    ##print(num)
                    search24(Selected,2,0,num,num)
                    TupleList.append(num)
                    Selected[j]=0
        Selected[i]=0


def calc24(numList,b=-1,c=-1,d=-1):
    global poExprist,TotalList,Selected 
    Selected=[0]*4
    TotalList=[]
    if d==-1:
        poExprist=numList
    else:
        poExprist=[numList,b,c,d]
    chooseTwo()



