x=[1001.7, 975.0, 978.3, 988.3, 978.7, 988.9, 1000.3, 979.2, 968.9, 983.5, 999.2, 985.6]

#a. find a 95% confidence interval for the average velocity of shells of this type

#add and subtract two std from the mean bcs of the rule 68-95-99.something

#std=the standard deviation
#tinv=the critical value for the t-distribution (inverse of the cdf).

#confidence = input('conf interv = ');
confidence = 0.95
alph = 1-confidence;

m1=mean(x)-std(x)/sqrt(length(x))*tinv(1-alph/2,length(x)-1);
m2=mean(x)+std(x)/sqrt(length(x))*tinv(1-alph/2,length(x)-1);

fprintf("the interval is (%f, %f)\n", m1, m2)



#b. at the 1% significance level, does the data suggest thet, on average, the muzzles are faster than 995 m/s
#1% sign => more significant, less evidence to reject h

alpha=0.1
m0=995

n=columns(x);

[H, P, CI, stat] = ttest(x, m0, "alpha", alpha, "tail", "right");
%H = the reject/acc of the hypoth, P = the P-value, CI = the conf interval, zstat = the value of the test



t1 = tinv(1 - alpha, n-1); % quantile for right-tailed test
RR = [t1, Inf]; % rejection region for right-tailed test
fprintf('the rejection region is (%4.4f,%4.4f)\n', RR)


fprintf("The value of the test statistic is %6.4f.\n", stat.tstat)



if H==0
  fprintf('H not rejected, the muzzles are faster than 995 m/s.\n')
else
  fprintf('H rejected, the muzzles are not faster than 995 m/s.\n')
end






