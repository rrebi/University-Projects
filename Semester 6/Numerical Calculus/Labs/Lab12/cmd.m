#1
#f(x)=x-e^(-x)
#f=@(x) x-exp(-x);
#fplot(f,[-1,2])

#[z,ni]=bisect(f,0,1,10^(-5),50)

#idk
#[z,ni]=secant(f,0,1,10^(-5),50)

#fd=@(x)+exp(-x)
#[z,ni]=newton(f,fd,0,10^(-5),50)

#2
#pkg load symbolic
p=[1,2,-4,-14,-5];
roots(p)
syms x
f=@(x) x^4+2*x^3-4*x^2-14*x-5
solve(f(x)==0)
fsolve(f,0)

bisect(f,-1,0,10^(-5),50)
secant(f,-1,0,10^(-5),50) #idk

fd=@(x) 4*x^3+6*x^2-8*x-14
#or 3+i or -1.5-1.5i
newton(f,fd,-1.5-1.5*i,10^(-5),50)
