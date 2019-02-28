#include <iostream>
using namespace std;
 
int main () {

	const size_t N = 3; // the dimension of the matrix
	int** matrix = new int*[N]; // each element is a pointer to an array.

	for(size_t i = 0; i < N; ++i)
		matrix[i] = new int[N]; // build rows

	for(size_t i = 0; i < N; ++i)  // filling up matrix
		{
		for(size_t j = 0; j < N; ++j)
			{
			matrix[i][j] = i+j;
			}
		}

	// printing matrix
	// for loop execution
	for( int i = 0; i < N; i = i + 1 ) {
	for (int j = 0; j < N; j = j + 1){
                cout << "M[" << i << ']' << '['<< j << "] = " << matrix[i][j] << endl;
		}
	}


	// DON'T FORGET TO DELETE THE MATRIX!
	for(size_t i = 0; i < N; ++i)
		delete matrix[i];

	delete matrix; 
   return 0;
}
