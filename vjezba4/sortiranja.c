#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <stdbool.h>
#include "sortiranja.h"

bool choose_pivot = true;

int n_min;

// pomocne funkcije
int *generiraj(int n)
{
	int *niz = (int *)malloc(sizeof(int) * n);
	niz[0] = rand() % 5;
	for (int i = 1; i < n; i++)
	{
		niz[i] = niz[i - 1] + rand() % 5;
	}
	return niz;
}

void shuffle(int *niz, int n)
{
	for (int i = 0; i < n; i++)
	{
		int k1 = rand() % n;
		int tmp = niz[i];
		niz[i] = niz[k1];
		niz[k1] = tmp;
	}
}

/*void print(int *niz, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%d ", niz[i]);
	}
	printf("\n");
}*/

// selection sort SLOZENOST N*N
void selectionsort(int *niz, int n)
{
	int i;
	for (i = 0; i < n - 1; i++)
	{ //I JE GRANICA NESORTIRANOG I SORTIRANOG
		int j, tmp, maxi = i;
		for (j = i + 1; j < n; j++)
		{
			if (niz[j] < niz[maxi])
				maxi = j;
		}

		tmp = niz[maxi]; //SORTIRANJE LIJEVE STRANE
		niz[maxi] = niz[i];
		niz[i] = tmp;
	}
}

// insertion sort  - SLOZENOST N*N
void insertionsort(int *niz, int n)
{
	int i;
	for (i = 1; i < n; i++)
	{ //I JE GRANICA
		int j = i;
		while (j > 0 && niz[j - 1] > niz[j])
		{ //SLAZE LIJEVU STRANU
			int tmp;
			tmp = niz[j - 1];
			niz[j - 1] = niz[j];
			niz[j] = tmp;
			j--;
		}
	}
}
/////////////GORNJI ALGORITMI BOLJI ZA MANJE NIZOVE//////////////
////////////DONJI ALGORITMI NA PODIJELI PA VLADAJ//////////////
// quick sort  N*logN
int partition(int *niz, int n)
{
	int l, r;
	l = 1; //BROJ PRIJE JE PIVOT
	r = n - 1;

	if (choose_pivot = true)
	{
		int tmp;
		if (niz[0] < niz[n / 2] && niz[n / 2] < niz[n - 1] && niz[0] < niz[n - 1] || niz[0] > niz[n / 2] && niz[n / 2] > niz[n - 1] && niz[0] > niz[n - 1])
		{
			tmp = niz[n / 2];
			niz[n / 2] = niz[0];
			niz[0] = tmp;
		}
		else if (niz[0] < niz[n / 2] && niz[n / 2] > niz[n - 1] && niz[0] < niz[n - 1] || niz[0] > niz[n / 2] && niz[n / 2] < niz[n - 1] && niz[0] > niz[n - 1])
		{
			tmp = niz[n - 1];
			niz[n - 1] = niz[0];
			niz[0] = tmp;
		}
	}

	while (l < r)
	{ //DOK DONJA GRANICA JE MANJA OD GORNJE
		if (niz[r] >= niz[0])
		{ //AKO JE ELEMENT GORNJE GRANICE VECI OD ELEMENTA NA NULTOJ POZICIJI SPUSTI GRANICU ZA 1
			r--;
		}
		else if (niz[l] < niz[0])
		{ //AKO JE ELEMENT DONJE GRANICE MANJI OD ELEMENTA NA NULTOJ POZICIJI DIGNI GRANICU ZA 1
			l++;
		}
		else
		{
			int tmp = niz[l];
			niz[l] = niz[r];
			niz[r] = tmp;
		}
	}
	if (niz[0] < niz[r]) //ako je nulti element manji od elementa desne ruke
	{
		return 0;
	}
	else  //zamjenjuje element desne ruke i nulti element i vraca index desne ruke
	{
		int tmp = niz[r];
		niz[r] = niz[0];
		niz[0] = tmp;
		return r;
	}
}

void quicksort(int *niz, int n)
{
	if (n < 2)
	{
		return;
	}
	else if (n < 200)
	{
		int pi = partition(niz, n);
		int pocetno_vrijeme = clock();
		quicksort(niz, pi);
		int vrijeme_zavrsetka = clock();
		double vrijeme_izvodenja = (vrijeme_zavrsetka - pocetno_vrijeme) / CLOCKS_PER_SEC;
		if (measure(insertionsort, niz, n) < vrijeme_izvodenja)
		{
			n_min = n;
			insertionsort(niz, n_min);
		}
	}
	else
	{
		int pi = partition(niz, n);
		quicksort(niz, pi); //sortiraj livo od pivota
		quicksort(niz + pi + 1, n - pi - 1); //sortiraj desno od pivota
	}
}
void quicksort1(int* niz,int n){
	if(n>n_min){
		int pi = partition(niz, n);
		quicksort1(niz, pi);
		quicksort1(niz + pi + 1, n - pi - 1); 
	}
	else{
		insertionsort(niz,n);
	}
}

// merge sort
void merge(int *niz, int *niza, int na, int *nizb, int nb)
{
	// implemntirati merge funkciju
}

// alocira i vra�a kopiju niza
int *duplicate(int *niz, int n)
{
	int i;
	int *novi = (int *)malloc(sizeof(int) * n);
	for (i = 0; i < n; i++)
	{
		novi[i] = niz[i];
	}
	return novi;
}

void mergesort(int *niz, int n)
{
	// implementirati
}

// mjerenje vremena izvo�enja funkcije sortiranja
double measure(void (*sort)(int *niz, int n), int *niz, int n)
{
	int start_time = clock();
	sort(niz, n);
	int end_time = clock();
	return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
