#binopdf(1,1,0.5)
#pkg load statistics
#binopdf(1,1,0.5)
#binopdf(1,2,0.5)

#n=10
#p=0.3

##n=input('Nr of trials(n)=');
##p=input('Pr of succes(p)=');

##
##x=0:n;
##px=binopdf(x,n,p);
##plot(x,px,'+');
##
##xx=0:0.1:n;
##fx=binocdf(xx,n,p)
##hold on; plot(xx,fx)

#x=0
##p1=binopdf(0,3,0.5)
##fprintf('P(x=0)=%1.4f', p1);

#c x!=1
##p1=1-binopdf(1,3,0.5)
##fprintf('P(x!=1)=%1.4f', p1);

#d P(x<=2) P(x<2)
##binocdf(2,3,0.5)
##binocdf(1,3,0.5)

#P(x>=1) P(x>1)
##1-binocdf(0,3,0.5)
##1-binocdf(1,3,0.5)
##fprint(of every bino

n=1000
c=rand(3,n) #1-heads 0-tails
D=c<0.5
x=sum(D); clf;
hist(x)
