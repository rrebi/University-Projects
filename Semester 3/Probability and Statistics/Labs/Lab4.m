

clear
p=input("p= ");
x=0
N=input("N= "); #nr simulations(1 sim=n trials)

#1
%{
for i=1:N
  r=rand;
  x(i)=r<p;
 end

 U_x=unique(x);
 n_x=hist(x, length(U_x))

%}


#2
%{
 n=input("n= ")

 r=rand(n,N);
 x=sum(r<p)

 U_x=unique(x);
 n_x=hist(x, length(U_x))
 n_x/N

 k=0:n;
 p_k=binopdf(k,n,p)
 plot(k,p_k,'o',U_x,n_x/N,'*')
 %}

 #c) geometric (nr failures before suc)

 %{
 for i=1:N
   x(i)=0;
   while rand>=p
     x(i)=x(i)+1;
   endwhile
 endfor

 U_x=unique(x);
 n_x=hist(x, length(U_x))
 n_x/N

 k=0:10;
 p_k=geopdf(k,p)
 plot(k,p_k,'o',U_x,n_x/N,'*')
%}

#d

n=input("n= ");
y=0;

for i=1:N
  for j=1:n
    x(j)=0;

    while rand>=p
      x(j)=x(j)+1;
    endwhile
  endfor

  y(i)=sum(x);
endfor

U_y=unique(y);
n_y=hist(y, length(U_y))

k=0:50
p_k=nbinpdf(k,n,p)

plot(k,p_k,'o',U_y,n_y/N,'*')
