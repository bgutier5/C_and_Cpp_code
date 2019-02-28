#include <iostream>


int sum_numbers(int a, int b)
{    int summation;
     summation = a + b;
     return summation;
}

int main()
{  std::cout<< sum_numbers(3,4) << "\n"; 
   return 0; 
} 
