#include <iostream> 
using namespace std; 
  
int* fun(int length, int center) 
{
    int total_values;
    total_values = 2*length+1; 
    int* range_values = new int[total_values]; 
  
    /* Some operations on arr[] */
    range_values[0] = 10; 
    range_values[1] = 20; 
    range_values[2] = 30;
    return range_values; 
} 
  
int main() 
{
    int L, center;  
    L = 3;
    center = 0;
    int* list = fun(L, center); 
    cout << list[0] << " " << list[1] << " " << list[2] << endl; 
    return 0; 
} 
