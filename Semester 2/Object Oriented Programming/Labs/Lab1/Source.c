#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//a
//Compute the approximated value of square root of a positive real number. Use a given precision.


int squareRoot(int n)
/*
computing the integer part of the square root of n by binary search
input: n - integer, the given number
output: returns int, the square root of n
*/
{
    int left = 0, right = n;
    int mid;
    int ans = 0;

    while (left <= right) {
        mid = (left + right) / 2;
        if (mid * mid == n) {
            ans = mid;
            break;
        }
        if (mid * mid < n) {
            left = mid + 1;
            ans = mid;
        }
        else {
            right = mid - 1;
        }
    }
    return ans;
}

float squareRootPrecision(int n, int p, double sqr)
/*
computing the fractional part of the square root upto given precision
input: n - integer, the number
       p - integer, the precision
       sqr - integer, the square root of n
output: returns float, the square root of n
*/
{
    float increment = 0.1f;
    for (int i = 0; i < p; i++) {
        while (sqr * sqr <= n) {
            sqr += increment;
        }
        sqr = sqr - increment;
        increment = increment / 10; //0.01 and so on
    }
    return sqr;
}

void read_a()
/*
reads the number n and the precision for subpunct a
prints the squareroot of n
*/ 
{
    int sqr;
    float sqrp;
    int n, p;

    printf("Enter the number: ");
    scanf("%d", &n);

    printf("Enter the precision: ");
    scanf("%d", &p);
    /*if (scanf("%d", &p) > 0) {
        printf("p = %d\n", p);
    }
    else printf("You did not enter any number.\n");*/


    sqr = squareRoot(n);
    //float sqr1 = (float)sqr;
    double sqr1 = (double)sqr;
    sqrp = squareRootPrecision(n, p, sqr1);
    printf("\n");
    printf("The square root: %d", sqr);
    printf("\n");
    printf("The square root w/ precision: %.*f", p, sqrp);
    printf("\n\n");
}


//b
//Given a vector of numbers, find the longest contiguous subsequence such that the difference of any two consecutive elements is a prime number


int read_array(int v[], int* len)
/*
reads an array
input v - the array of int
      len - the length int
output -
*/
{
    printf("Enter the length of the array: ");
    int x = 0;
    scanf("%d", &x);
    *len = x;
    printf("Enter elements: ");
    for (int i = 0; i < *len; i++)
        scanf("%d", &v[i]);
}

int prime(int n)
/*
checks if n is prime
input  n int
output 0 - false
       1 - true         
*/
{
    if (n < 2) {
        return 0;
    }
    for (int i = 2;i <= n / 2;i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

typedef struct SEPoint 
// struct to return the start point and the end point of the subsequence 
{ 
    int start, end;
} SEPoint;

struct SEPoint longest_subsequence(int v[], int n)
/*
returns the start and the end points for the longest subsequence with dif = prime number
input n - the length- int
      v - the array of integers
output li - struct - SEPoint (start end point)
*/ 
{
    int max_l = -1, first_pos = -1;
    for (int i = 0; i < n - 1; i++) {
        int pos = i;
        int l = 1;
        while (i < n - 1 && prime(v[i] - v[i + 1]) && v[i] > v[i + 1]) {
            i++;
            l++;
        }
        if (l > max_l) {
            max_l = l;
            first_pos = pos;
        }

    }
    SEPoint li;
    li.start = first_pos;
    li.end = first_pos + max_l;
    return li;
}

void print_array(int v[], int start, int end)
/*
prints the array from start-end
input v - the array int
      start -int the first position
      end -int the 2nd position
output the array
*/
{
    printf("The longest increasing contiguous subsequence, such that the dif of any 2 consecutive elements is a prime number is:\n");

    for (int i = start; i < end; i++)
        printf("%d ", v[i]);

    printf("\n");
}

void print_array1(int v[], int n)
/*
prints the whole array
input v - the array int
      start -int the first position
      end -int the 2nd position
output the array
*/
{
    printf("The array is:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", v[i]);

    printf("\n");
}


//5a
// Print the exponent of a prime number p from the decomposition in prime factors of a given number n (n is a non - null natural number)


int prime_exponent(int n, int p)
/*
searches the exponent of p in n
input n - given number int
      p - the prime number that is searched
output exp - the exponent of p
*/
{
    int exp = 0;
    /*for (int i = 2; i <= n/2; i++)
    {
        while (n % i == 0)
        {
            p++;
            n = n / i;
        }
    }
    if (n > 2) //if n is prime => the exponent is 1
        return 1;
    */
    while (n % p == 0 && n!=1) {
        exp++;
        n = n / p;
    }   
    return exp;
}

void read_a_5() 
/*
reads the number n and returns the exponent of a prime number from the decomposition
*/ 
{
    int n, p;
    printf("Enter the number: ");
    scanf("%d", &n);
    printf("Enter the prime number: ");
    scanf("%d", &p);

    while (!prime(p)) {
        printf("Not a prime number!\n");
        printf("Enter the prime number: ");
        scanf("%d", &p);
    }
    int exp;
    exp = prime_exponent(n, p);
    printf("The exponent of a prime decomposition is: %d", exp);
    printf("\n");
}


int main()
{
    int ok = 0;
    int length = 0, v[101];

    while (ok == 0) {
        printf("1 - read a sequence\n2 - solve subp a.\n3 - solve sub b.\n4 - solve sub a.ex 5\n5 - exit\n\n");
        int option;
        printf("Enter an option: ");
        scanf("%d", &option);

        if (option == 1) {
            read_array(v, &length);
        }
        else if (option == 2) {
            read_a();
        }
        else if (option == 3) {
            //read_array(v, &length);
            print_array1(v, length);
            SEPoint l = longest_subsequence(v, length);
            print_array(v, l.start, l.end);
        }
        else if (option == 4) {
            read_a_5();
        }
        else if (option == 5) {
            ok = 1;
        }
        else {
            printf("Invalid option!\n");
        }
    }
    return 0;
}