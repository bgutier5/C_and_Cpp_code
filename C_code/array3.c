#include <stdio.h>
#include <string.h> 
void print_list(double list[]);

void print_list(double list[])
{
   printf("[");
   for (int i = 0; i < 5; i++)
       {if (i != 4){
	      printf("%3.1f, ", list[i]);
       } else {
              printf("%3.1f]\n", list[i]);
              }
       }
   return;
}


int main()
{  double rainfall[5];
   rainfall[0] = 2.3; 
   rainfall[1] = 0.3;
   rainfall[2] = 0.0; 
   rainfall[3] = 4.1; 
   rainfall[4] = 0.5;
   print_list(rainfall);
   memset(rainfall, 0, sizeof(rainfall));
   print_list(rainfall);
   return 0;
} 
