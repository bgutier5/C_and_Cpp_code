#include <iostream>
#include <math.h>
using namespace std;

// Parameters
const int n_osc = 6;
double mass = 1;
double k_constant = 1;
double k_coupling = 0.1;
void print_matrix(double list[][n_osc]);


// Define C interface with lapack 
extern "C" {
extern int dgeev_(char*,char*,int*,double*,int*,double*, double*, double*, int*, double*, int*, double*, int*, int*);
}
 
int main () {
   // filling up matrix
   int n = n_osc;
   double matrix[n_osc*n_osc];
   for(int i = 0; i < n; i++){
       for (int j=0; j < n; j++){
           if (i == j+1){
               matrix[i*n + j] = k_coupling/mass;
           }else if (i == j-1){
               matrix[i*n + j] = k_coupling/mass;
           }else if (i == j){
               matrix[i*n + j] = k_constant/mass;
           }else{
               matrix[i*n + j] = 0.0;
           }
       }
     
   }
   matrix[0*n + n-1 ] = k_coupling;
   matrix[(n-1)*n +0] = k_coupling;
   //print_matrix(matrix);

   // setting up lapack
   char Nchar='N';
   double *eigReal=new double[n];
   double *eigImag=new double[n];
   double *vl,*vr;
   int one=1;
   int lwork=6*n;
   double *work=new double[lwork];
   int info;

   // calculate eigenvalues using the DGEEV subroutine
   dgeev_(&Nchar,&Nchar,&n,matrix,&n,eigReal,eigImag,
         vl,&one,vr,&one,
         work,&lwork,&info);

   // check for errors
   if (info!=0){
     cout << "Error: dgeev returned error code " << info << endl;
     return -1;
   }
   
   // print eigenvalues and calculate total energy
   double total_energy = 0.0;
   cout << "--- Eigenvalues of K matrix ---" << endl;
   for (int i=0;i<n;i++){
     cout << "( " << eigReal[i] << " , " << eigImag[i] << " )\n";
     total_energy += 0.5 * sqrt(eigReal[i]);
   }
   cout << endl;

   // print total energy
   cout << "total energy = " << total_energy << endl; 
   
   // deallocate
   delete [] eigReal;
   delete [] eigImag;
   delete [] work;


   return 0;
}



void print_matrix(double matrix[][n_osc]){
    int n = n_osc;
    for( int i = 0; i < n; i = i + 1 ){
        cout << "[";
	for (int j = 0; j < n; j = j + 1){
		cout <<  matrix[i][j] ;
                if (j < n - 1){
                   cout << ", ";
                } else {
                   cout << "]" << endl;
                     } 
                }
        }
    return;
    }
