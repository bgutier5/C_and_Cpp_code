#include <iostream>
#include <fstream>


//  **** Description ****
/* This is the BARE MININUM example of eigenvalues function of lapack.

Command to compile code
$ g++ -o lapacke_example9_2.out lapacke_example9_2.cpp  -llapack


The output should be: 
--- Eigenvalues ---
( 6.15484 , 0 )
( -2.07742 , 3.50095 )
( -2.07742 , -3.50095 )

first column are the real part of the eigenvalues, and the second column are the imaginary parts.
*/

using namespace std;

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int dgeev_(char*,char*,int*,double*,int*,double*, double*, double*, int*, double*, int*, double*, int*, int*);
}

int main(int argc, char** argv){


  int n=3;
  int m=3;
  //double *data;

  double data[9] = {-1.0,-8.0, 0.0,
                    -1.0, 1.0,-5.0,
                     3.0, 0.0, 2.0};
  

  // allocate data
  char Nchar='N';
  double *eigReal=new double[n];
  double *eigImag=new double[n];
  double *vl,*vr;
  int one=1;
  int lwork=6*n;
  double *work=new double[lwork];
  int info;

  // calculate eigenvalues using the DGEEV subroutine
  dgeev_(&Nchar,&Nchar,&n,data,&n,eigReal,eigImag,
        vl,&one,vr,&one,
        work,&lwork,&info);


  // check for errors
  if (info!=0){
    cout << "Error: dgeev returned error code " << info << endl;
    return -1;
  }

  // output eigenvalues to stdout
  cout << "--- Eigenvalues ---" << endl;
  for (int i=0;i<n;i++){
    cout << "( " << eigReal[i] << " , " << eigImag[i] << " )\n";
  }
  cout << endl;

  // deallocate
  delete [] eigReal;
  delete [] eigImag;
  delete [] work;


  return 0;
}
