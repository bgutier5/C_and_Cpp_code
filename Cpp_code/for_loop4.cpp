#include <iostream>
using namespace std;

int main () {
    // declaring variables
    int lower, upper;
    lower = -5;
    upper =  6;

    for( int a = lower; a < upper; ++a) {
       cout << "The value of the loop is: " << a << endl; 
    }

    return 0;
}
