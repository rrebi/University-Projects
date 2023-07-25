x=[7 7 4 5 9 9 ...
   4 12 8 1 8 7 ...
   3 13 2 1 17 7 ...
   12 5 6 2 1 13 ...
   14 10 2 4 9 11 ...
   3 5 12 6 10 7];
l=input("alpha: ")
s = 5;
t = 9;
[h, p, ci, zstat] = ztest(x,t,s, "alpha", l,'tail', 'left')

##
##if h==1
## fprintf('the h is rejected');
##else
## fprintf('the h is ac');


fprintf('the value of the statistic =%4.4f \n',zstat);
fprintf('the p value =%4.4f \n',p);

rr = [-inf, norminv(l)]
fprintf('rejection region is (%1.1f, %1.1f)\n',rr);


#b
#strictly >
[h,p,ci,tstat]=ttest(x,t, "alpha", l,'tail', 'right')


#fprintf('the value of the statistic =%4.4f \n',tstat);
fprintf('the p value =%4.4f \n',p);
rr1=[tinv(1-l,n-1),inf]

fprintf('rejection region is (%1.1f, %1.1f)\n',rr1);
