#include <stdio.h>
#include <string.h> 

int main()
{  double rainfall[5];
   rainfall[0] = 2.3; 
   rainfall[1] = 0.3;
   rainfall[2] = 0.0; 
   rainfall[3] = 4.1; 
   rainfall[4] = 0.5;
   //printf("%6.1f\n", rainfall[5]);
   printf("[ ");
   for (int i = 0; i < 5; i++)
       {if (i != 4){
	      printf("%3.1f, ", rainfall[i]);
       } else {
              printf("%3.1f ]\n", rainfall[i]);
              }
       }
   memset(rainfall, 0, sizeof(rainfall));
   //rainfall[5] = {0};
   printf("[ ");
   for (int i = 0; i < 5; i++)
       {if (i != 4){
	      printf("%3.1f, ", rainfall[i]);
       } else {
              printf("%3.1f ]\n", rainfall[i]);
              }
       }
   return 0;
} 
