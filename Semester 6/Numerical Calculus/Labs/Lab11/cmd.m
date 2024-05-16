%1 Romberg’s method
#vpa(pi*sqrt(3)/9,6); %0.6

#f=@(x) 1./(2+sin(x));
#[I,nfev]=romberg(f,0,pi/2,10^-6,50);


%2 Gaussian quadrature
#f=@(x) sqrt(1-x.^2) #interval [1,-1]
[I,gn,gc]=gauss_quad(@(x)(x.^2+1)./(x.^2+1),2,3)
I*2

%3 n=5
n=5;
#integral(@(x)exp(cos(x)),0,pi/4)
#gauss_quad(@(x)(x.^2+1)./(x.^2+1),25,1)*2

%4 n=4
n=4;
%a laguerre val=1/2

%b Hermite idk

%c Chebyshev 1
f=@(x)sin(x.^2);
[I,gn,gc]=gauss_quad(f,4,2)
I*2
