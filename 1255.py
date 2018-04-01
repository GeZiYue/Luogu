a,b=1,2
n=int(input())
if(n==0):
    print(0)
    exit(0)
if(n==1):
    print(1)
    exit(0)
n-=2
while n:
    b=a+b
    a=b-a
    n-=1
print(b)
