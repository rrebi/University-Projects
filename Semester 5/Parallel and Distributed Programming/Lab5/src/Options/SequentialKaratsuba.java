package Options;

import Models.Polynomial;
import Utils.KaratsubaUtils;

public class SequentialKaratsuba {
    public static Polynomial multiply(Polynomial p1, Polynomial p2) {
        if (p1.getDegree() < 2 || p2.getDegree() < 2) {
            return SequentialClassic.multiply(p1, p2);
        }

        // len for splitting the polynomials
        int len = Math.max(p1.getDegree(), p2.getDegree()) / 2;

        Polynomial lowP1 = new Polynomial(p1.getCoefficients().subList(0, len));
        Polynomial highP1 = new Polynomial(p1.getCoefficients().subList(len, p1.getCoefficients().size()));
        Polynomial lowP2 = new Polynomial(p2.getCoefficients().subList(0, len));
        Polynomial highP2 = new Polynomial(p2.getCoefficients().subList(len, p2.getCoefficients().size()));


        Polynomial z1 = multiply(lowP1, lowP2);  // z1 = (a0 + a1x) * (b0 + b1x)
        Polynomial z2 = multiply(KaratsubaUtils.add(lowP1, highP1), KaratsubaUtils.add(lowP2, highP2));  // z2 = (a0 + a1x + a2x^2) * (b0 + b1x + b2x^2)
        Polynomial z3 = multiply(highP1, highP2);  // z3 = (a2x^2) * (b2x^2)

        // compute final result
        Polynomial r1 = KaratsubaUtils.addWithZeros(z3, 2 * len);  // r1 = z3 * x^2. highest degree
        Polynomial r2 = KaratsubaUtils.addWithZeros(KaratsubaUtils.subtract(KaratsubaUtils.subtract(z2, z3), z1), len);  // r2 = (z2 - z3 - z1) * x. middle degree
        return KaratsubaUtils.add(KaratsubaUtils.add(r1, r2), z1);  // finalResult = r1 + r2 + z1
    }
}