function I=simpson(f,a,b,n)
  h=(b-a)/(2*n);
  s1=sum(f(a+([1:n]*2-1)*h)); #x4
  s2=sum(f(a+([1:n-1]*2)*h)); #x2
  I=h/3*(f(a)+4*s1+2*s2+f(b));
end
