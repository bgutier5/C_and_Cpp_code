#include <iostream>

// This one works
/*

Compiling commands (two steps)
g++ -O -c myprog.cc
g++ myprog.o -o myprog -L/usr/local/lib64 -llapack -lblas -lgfortran -lm

Compiling commands (one step)
g++ -O myprog.cc -o myprog -L/usr/local/lib64 -llapack -lblas -lgfortran -lm

*/


extern "C" {
     void dgesv_(int *n, int *nrhs,  double *a,  int  *lda,  
           int *ipivot, double *b, int *ldb, int *info) ;
}



#define MAX 10

int main(){
   // Values needed for dgesv
   int nrhs = 1;
   int lda = MAX;
   int ldb = MAX;
   int ipiv[MAX];
   int info;
   // Other values
   int i,j;

   // Declared matrices/arrays
   int n = 3;
   double a[MAX][MAX] = {{1,2,3},  
                         {2,3,4},   
                         {3,4,1}};

   double b[1][MAX] = {-4,-1,-2}; 



   // Solve the linear system
   dgesv_(&n, &nrhs, &a[0][0], &lda, ipiv, &b[0][0], &ldb, &info);

   // Check for success
   if(info == 0)
   {
      // Write the answer
      std::cout << "The answer is\n";
      for(i = 0; i < n; i++)
        std::cout << "b[" << i << "]\t" << b[0][i] << "\n";
   }
   else
   {
      // Write an error message
      std::cerr << "dgesv returned error " << info << "\n";
   }
   return info;
}
