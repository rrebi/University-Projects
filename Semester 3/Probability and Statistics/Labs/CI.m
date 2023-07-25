#lab5
function [m1,m2]=CI(x,sigma,alpha)
  n = length(x);
  m1=mean(x) - (sigma/(sqrt(n)) * norminv(1 - alpha/2));
  m2=mean(x) + (sigma/(sqrt(n)) * norminv(1 - alpha/2));

