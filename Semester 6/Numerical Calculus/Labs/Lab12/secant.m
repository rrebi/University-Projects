function [z,ni]=secant(f,x0,x1,err,maxn)
  for k=1:maxn
    x2=x1-f(x1)*(x0-x1)/(f(x0)-f(x1));
    if abs(x2-x1)<err
      z=x2;
      ni=k;
      return
    endif
    x0=x1;
    x1=x2;
    error('too difficult');
  endfor
end
