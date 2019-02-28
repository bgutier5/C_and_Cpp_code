#include <iostream>
using namespace std;

int* get_range_at(int center, int L)
{   
    // setting up variables
    int total_values, lower, upper;
    total_values = 2*L+1;
    lower = center - L;
    upper = center + L;

    // creating and populating array
    int* range_values = new int [total_values];
    for( int i = 0; i < total_values; ++i)
    {   range_values[i] = center-L+i;
    }
    return range_values; 
}


int main () {

    // declaring variables
    int L, center, total;
    L = 3;
    center = 2;
    total = 2*L+1;

    // obtaining the populated array
    int* arr = get_range_at(center, L);

    // printing out array
    for (int i = 0; i < total; ++i)
    {    cout << arr[i] << endl;}
    
    return 0;
}
