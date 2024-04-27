%ex 1
log(2); #0.693
f=@(x)1./x;

#rectangle method
rect(f,1,2,13) #13 for first 3 decimals; 20 for first 4

#trapezoid method
trapezoid(f,1,2,10)

#simpsons method
simpson(f,1,2,10)


#adaptive quadratures
%ex 4
f=@(x)sin(pi*x);
g=@(x)sqrt(1+(pi*cos(pi*x)).^2);
adaptquad(g,0,1,10^(-6),@simpson,4)
