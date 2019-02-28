#include <iostream>
#include <fstream>


//  **** Description ****
/* This is working example of the eigenvalue function dgeev. In order to work, several things need to be accounted for
    1. The matrix is stored on a separate text file (matrix.txt), which is fed to the compiled code (details below)
    2. The linking to lapack is done with a very specific command (details below)

Command to compile code
$ g++ -o lapacke_example9.out lapacke_example9.cpp  -llapack

Feeding matrix file and running
./lapacke_example9 matrix.txt

The output should be: 
--- Eigenvalues ---
( 6.15484 , 0 )
( -2.07742 , 3.50095 )
( -2.07742 , -3.50095 )

*/

using namespace std;

// dgeev_ is a symbol in the LAPACK library files
extern "C" {
extern int dgeev_(char*,char*,int*,double*,int*,double*, double*, double*, int*, double*, int*, double*, int*, int*);
}

int main(int argc, char** argv){

  // check for an argument
  if (argc<2){
    cout << "Usage: " << argv[0] << " " << " filename" << endl;
    return -1;
  }

  int n,m;
  double *data;

  // read in a text file that contains a real matrix stored in column major format
  // but read it into row major format
  ifstream fin(argv[1]);
  if (!fin.is_open()){
    cout << "Failed to open " << argv[1] << endl;
    return -1;
  }
  fin >> n >> m;  // n is the number of rows, m the number of columns
  data = new double[n*m];
  for (int i=0;i<n;i++){
    for (int j=0;j<m;j++){
      fin >> data[j*n+i];
    }
  }
  if (fin.fail() || fin.eof()){
    cout << "Error while reading " << argv[1] << endl;
    return -1;
  }
  fin.close();

  // check that matrix is square
  if (n != m){
    cout << "Matrix is not square" <<endl;
    return -1;
  }

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
  delete [] data;
  delete [] eigReal;
  delete [] eigImag;
  delete [] work;


  return 0;
}
