#include <iostream>
#include <math.h>
#include <vector>
#include <tuple>
#include <cstdlib>

using namespace std;

// Parameters
int states_per_oscillator = 2;
const int n_osc = 3;
double mass = 1;
double k_constant = 1;
double k_coupling = 0.1;
int hbar = 1;
int n_states = pow( states_per_oscillator, n_osc );
void print_matrix(double matrix[]);


// Define C interface with lapack 
extern "C" {
extern int dgeev_(char*,char*,int*,double*,int*,double*, double*, double*, int*, double*, int*, double*, int*, int*);
}

vector<int> change_of_basis(int number){
    vector<int> ivals;
    int residue, pad;
    while (number > 0){
        residue = number%states_per_oscillator;
        number = number/states_per_oscillator;
        ivals.push_back(residue);
        }
    pad = n_osc - ivals.size();
    for (int j = 0; j < pad; j++ ){
        ivals.push_back(0);
        }
    return ivals;
}

vector<vector<int>> compare(vector<int> bra, vector<int> ket){
    vector<vector<int>>  diff;
    vector <int> set;
    for (int i=0; i < n_osc; i++){
        if (bra[i] != ket[i]){
            set = {i, bra[i], ket[i]}; 
            diff.push_back(set);
            }
        }
    return diff;
    }


double H_matrix(vector<int> bra, vector<int> ket){
    int position1,bra1,ket1,position2,bra2,ket2, position_m, bra_m, ket_m;
    double v = 0.0;
    vector<vector<int>> diff;
    diff = compare(bra, ket);
    if(diff.size() == 2 ){
       position1 = diff[0][0]; 
       bra1      = diff[0][1]; 
       ket1      = diff[0][2]; 
       position2 = diff[1][0]; 
       bra2      = diff[1][1]; 
       ket2      = diff[1][2];
       if( position2 - position1 == 1 || position2 - position1 == n_osc - 1 ){
          double p = 0.0;
          for(int m=0; m<2; m++){
              if( (abs(bra1 - ket1) == 1) and (abs(bra2 - ket2) == 1) ){
                  double pi = 0.0;
                  position_m = diff[m][0];
                  bra_m      = diff[m][1];
                  ket_m      = diff[m][2];
                  if(bra_m - ket_m == 1){
                      pi = ( sqrt(hbar/ (2 * sqrt(mass * k_constant) )  ) ) * (sqrt(ket_m + 1 )); 
                      } 
                  if(bra_m - ket_m == -1){
                      pi = ( sqrt(hbar/ (2 * sqrt(mass * k_constant))  ) ) * (sqrt(ket_m));
                      }
                  if (v == 0.0){
                      v = k_coupling * pi;
                      }
                  else{
                      v *= pi;
                      }
                  }
              } 
           } 
        }
    return v; 
    }
 
int main () {

    vector<vector<int>> mydiff;
    vector<int> bra;
    vector<int> ket;
    double ei, temp;
    double matrix[ n_states*n_states ];
    for(int i=0; i<n_states; i++){
        ket = change_of_basis(i);
        for(int j=0; j<n_states;j++){
            bra = change_of_basis(j);
            matrix[i*n_states + j] = H_matrix(bra, ket);
            }
        ei=0.0;
        for(int k=0; k<n_osc; k++){
            temp  = (ket[k] + 0.5) * hbar * sqrt(k_constant);
            ei += temp;
            }
        matrix[i*n_states + i] = ei; 
        }
   print_matrix(matrix);
    //for(int i=0; i<n_states; i++){
    //    for(int j=0; j<n_states;j++){
    //        cout << matrix[i*n_states + j] << "    ";
    //        }
    //    cout << endl;
    //    }


   int n = n_states;
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
   cout << "--- Eigenvalues of K matrix ---" << endl;
   for (int i=0;i<n;i++){
       cout << "( " << eigReal[i] << " , " << eigImag[i] << " )\n";
   }
   cout << endl;

   // print total energy
   cout << "total energy = " << eigReal[0] << endl; 
   
   // deallocate
   delete [] eigReal;
   delete [] eigImag;
   delete [] work;

   return 0;
}


void print_matrix(double matrix[]){
    int n = pow( states_per_oscillator, n_osc );
    for( int i = 0; i < n; i = i + 1 ){
        cout << "[";
	for (int j = 0; j < n; j = j + 1){
		cout <<  matrix[i*n + j] ;
                if (j < n - 1){
                   cout << ",     ";
                } else {
                   cout << "]" << endl;
                     } 
                }
        }
    return;
    }
