#include <stdio.h>


double sum_numbers(double a, double b)
{    double summation;
     summation = a + b;
     return summation;
}

int main()
{  printf("%6.2f\n", sum_numbers(3.51,4.5));
   return 0;
}

