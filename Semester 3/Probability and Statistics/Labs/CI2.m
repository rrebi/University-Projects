#lab5
function [m1,m2]=CI2(x,alpha)
  v = var(x);
  n = length(x);
  m1=(v*(n-1)) / (chi2inv(1 - alpha/2,n-1));
  m2=(v*(n-1)) / (chi2inv(alpha/2,n-1));

