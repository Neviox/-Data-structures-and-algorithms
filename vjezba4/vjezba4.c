#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sortiranja.h"
#include "sortiranja.c"

int n_min;

void main()
{ /*
  for (int i =0; i <= 100000; i += 10000)
  {
    int *niz1 = generiraj(i);
    int *niz2 = generiraj(i);
    shuffle(niz1, i);
    shuffle(niz2, i);


    choose_pivot = true;

    double vrijeme1 = measure(quicksort, niz1, i);
    double vrijeme2 = measure(quicksort, niz1, i);
    printf("Nesortirani niz s pivotom %lf sec             i=%d\n", vrijeme1, i);
    printf("Sortirani niz s pivotom = %lf sec                i=%d\n \n", vrijeme2, i);

    choose_pivot = false;

    double vrijeme3 = measure(quicksort, niz2, i);
    double vrijeme4 = measure(quicksort, niz2, i);
    printf("Nesortirani niz bez pivota = %lf sec               i=%d \n", vrijeme3, i);
    printf("Sortirani niz bez pivota = %lf sec                  i=%d \n\n\n", vrijeme4, i);

    free(niz1);
    free(niz2);
  }*/
  //Dodati novu, izmijenjenu, quicksort funkciju tako da za neku dužinu primljenog niza n koja je manja od nekog n_min, zove selectionsort ili insertionsort funkciju umjesto rekurzivnog poziva quicksort funkcije.
  // Pronaći optimalni n_min mjerenjem vremena izvođenja za različite vrijednosti u rasponu [0 .. 200] sa korakom 5 (prilagoditi po potrebi). Da
  int n = 5000000;
  int *niz3 = generiraj(n);
  shuffle(niz3, n);
  
  for (n_min = 5; n_min < 200; n_min += 5)
  {
    int *niz4 = duplicate(niz3, n);
    double vrqst;
    vrqst = measure(quicksort1, niz4,n);
    printf("n_min je %d  , vrijeme qsrt1 je %lf\n",n_min,vrqst);

     


    
    free(niz4);
  }
  free(niz3);
  
}