#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


int comparator(const void * a, const void * b) {
   double ai = *(double *)a;
   double bi = *(double *)b;
   if (ai - bi < 0) return -1;
   else if (ai == bi) return 0;
   return 1;
}

int main () {
   int i, n;
   
   n = 15;

   double array[15];
   
   /* Intializes random number generator */
   srand(time(0));
   /* Print 5 random numbers from 0 to 49 */
   for(i = 0 ; i < n ; i++) {
      array[i] = rand() % 50 + (double) rand() / RAND_MAX;
   }

   qsort((void *)array, 15, sizeof(double), comparator);

   for (int i = 0; i < 15; i++){
      printf("%lf\n", array[i]);
   }
   
   
   return(0);
}