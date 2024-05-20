function [z,ni]=bisect(f,a,b,err,maxn)
  c=(a+b)/2;
  fa=f(c); fb=f(b);
  if sign(fa) * sign(fb) > 0
    error('wrong sign');
    return
  endif

  c=(a+b)/2;

  for k=1:maxn
    fc=f(c);
    if sign(fb) * sign(fc)<=0
      a=c;
      fa=fc;
    else
      b=c;
      fb=fc;
    endif
    if abs(b-a)<err
      z=c;
      ni=k;
      return
    endif
    c=(a+b)/2;
  endfor
  error('too different');
end
