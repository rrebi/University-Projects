function I=rect(f,a,b,n)
  h=(b-a)/n;
  s=sum(f(a+([0:n-1]+1/2)*h));
  I=h*s;
end
