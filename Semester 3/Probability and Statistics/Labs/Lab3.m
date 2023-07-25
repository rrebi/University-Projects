#1
#a)
#   p1=P(x<=0)=normcdf(0,n,t)
#   p2=P(x>=0)=1-p1
#   P(x=0)=0

#b)
#   p3=P(-1<=x<=1)=normcdf(1,n,t)-normcdf(-1,n,t)
#   p4=P(x<=-1 or x>=1)=1-p3

#n=1 t=5;
#n=input("n=")
#t=input("t=")

#p1=normcdf(0,n,t)
#1-normcdf(0,n,t)

#normcdf(1,n,t)-normcdf(-1,n,t)
#1-normcdf(1,n,t)+normcdf(-1,n,t)


#
a=input("a=")
b=input("b=")

option=input('opt=','s')

switch option
  case 'normal'
    n=input("n=")
    t=input("t=")

    p1=normcdf(0,n,t)
    p2=1-p1

    p3=normcdf(1,n,t)-normcdf(-1,n,t)
    p4=1-p3

    p5=norminv(a,n,t)
    p6=norminv(1-b,n,t)

  case 'student'
    n=input("n=")
    p1=tcdf(0,n)
    p2=1-p1
    p3=tcdf(0,n)-tcdf(0,n)
    p4=1-p3
    p5=tinv(a,n)
    p6=tinv(1-b,n)

  case 'fisher'
    n=input("n=")
    t=input("t=")
    p1=fcdf(0,n,t)
    p2=1-p1
    p3=fcdf(0,n,t)-fcdf(0,n,t)
    p4=1-p3
    p5=finv(a,n,m)
    p6=finv(1-b,n,m)
  end


