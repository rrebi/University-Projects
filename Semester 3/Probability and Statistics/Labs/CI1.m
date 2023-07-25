#lab5
function [m1,m2]=CI1(x,alpha)
  s = std(x);
  n = length(x);
  m1=mean(x) - (s/(sqrt(n)) * tinv(1 - alpha/2,n-1));
  m2=mean(x) + (s/(sqrt(n)) * tinv(1 - alpha/2,n-1));

