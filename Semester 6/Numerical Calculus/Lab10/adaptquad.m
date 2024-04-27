function I=adaptquad(f,a,b,eps,met,m) #met=@rectangle, @trapez, @simpson
  I1=met(f,a,b,m);
  I2=met(f,a,b,2*m);
  if abs(I1-I2)<eps
    I=I2
  else
    I=adaptquad(f,a,(a+b)/2,eps,met,m)+adaptquad(f,(a+b)/2,b,eps,met,m)
  endif
end
