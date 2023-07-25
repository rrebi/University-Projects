#b)

n=input("n= ");
p=input("p= ");
lambda=n*p;
k=0:n;
p1=poisspdf(k,lambda);
p2=binopdf(k,n,p);
plot(k,p1,k,p2);
