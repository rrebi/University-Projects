#2
#a)

p = input("Prob: ");
for n = 1:3:100;
  k = 0:n;
  pb = binopdf(k, n, p);
  plot(pb);
  pause(0.2);
end;


