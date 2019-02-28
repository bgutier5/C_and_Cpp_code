#include <iostream>
#include <iomanip>

using namespace std;
 
int main () {
   const size_t n = 3;
   int matrix[n][n] = {{1,2,3},  // you cannot change the size of matrix dimension
		       {4,5,6},  // unless you specify it with const 
		       {7,8,9}
                      };
   int matrix2[n][n] = {{4,6,2},
			{2,3,4},
			{3,3,3}
		       };
   int matrix3[n][n];


   // matrix multiplication
   for(int a=0; a < n; a++){
       for(int b=0; b < n; b++){
           int temporary_element = 0;       // you have to create it in order to store the value, otherwise if you assign it directly nonsense will appear
           for(int c = 0; c < n; c++){
	       temporary_element += matrix[a][c]*matrix2[c][b];
               }
           matrix3[a][b] = temporary_element;
           }
       }


   // printing matrix to screen
   for( int x = 0; x < n; x = x++  ) {
	for (int y = 0; y < n; y = y++){
		cout <<  matrix3[x][y] <<  "  ";
                }
	cout << endl;
        }
 
   return 0;
}
