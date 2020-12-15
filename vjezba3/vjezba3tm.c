#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

int *generiraj(int n)
{
	int *niz = (int *)malloc(sizeof(int) * n);
	niz[0] = rand() % 5;
	for (int i = 1; i < n; i++)
	{
		niz[i] = niz[i - 1] + 1 + rand() % 5;
	}
	return niz;
}
void shuffle(int *niz, int n)
{
	for (int i = 0; i < n; i++)
	{
		int stvarna = i;
		int random = rand() % n;
		int temp = niz[stvarna];
		niz[stvarna] = niz[random];
		niz[random] = temp;
	}
}
int *presjek(int *niz1, int *niz2, int n1, int n2, int *n3)
{
	int *niz3 = (int *)malloc(sizeof(int) * n1);
	int brojac = 0;
	for (int i = 0; i < n1; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			if (niz1[i] == niz2[j])
			{
				niz3[*n3] = niz1[i];
				(*n3)++;
				break;
			}
		}
	}
	//printf("%d", *n3);
	niz3 = (int *)realloc(niz3, *n3 * sizeof(int));
	return niz3;
}

int cmpfunc(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}
int *presjek_sortirani(int *niz1, int *niz2, int n1, int n2, int *n4)
{

	int *niz4 = (int *)malloc(sizeof(int) * n1);
	int *p;
	for (int i = 0; i < n1; i++)
	{
		p = (int *)bsearch(&(niz1[i]), niz2, n2, sizeof(int), cmpfunc);
		if (p != NULL)
		{
			niz4[*n4] = *p;
			(*n4)++;
		}
	}
	//printf("%d", *n4);
	niz4 = (int *)realloc(niz4, *n4 * sizeof(int));
	return niz4;
}

void main()
{
	int n1 = 30000;
	int n2 = 10000;
	int n3 = 0, n4 = 0;
	int *niz1, *niz2, *niz3, *niz4;
	srand(time(NULL));
	//niz1 = generiraj(n1);
	//niz2 = generiraj(n2);
	//shuffle(niz1, n1);
	//niz3 = presjek(niz1, niz2, n1, n2,&n3);
	/*for (int i = 0; i < n3; i++) {
		printf("%d\n",niz3[i]);
	}*/
	//niz4 = presjek_sortirani(niz1, niz2, n1, n2, &n4);
	/*for (int i = 0; i < n1; i++) {
		printf("%d",niz4[i]);
	}*/
	printf("Prvi krug__________________________________________________\n \n");
	printf("############ Niz 1 fiksan , niz 2 promjenjiv  ############# \n");
	for (; n2 <= 50000; n2 += 5000)
	{
		printf("Iteracija = %d\n", n2);
		niz1 = generiraj(n1);
		shuffle(niz1, n1);
		niz2 = generiraj(n2);
		shuffle(niz2, n2);

		//IZRACUN DVA NESORITANA

		clock_t start1 = clock();
		niz3 = presjek(niz1, niz2, n1, n2, &n3);
		clock_t stop1 = clock();
		double ellapsed1 = ((double)stop1 - start1) / CLOCKS_PER_SEC;
		printf("Vrijeme presjeka 2 nesortirana niza= %f sec ! \n", ellapsed1);
		free(niz3);

		/// IZRACUN SORTIRANOG I NESORTIRANOG

		clock_t start2 = clock();
		niz4 = presjek_sortirani(niz1, niz2, n1, n2, &n4);
		clock_t start3 = clock();
		qsort(niz2, n2, sizeof(int), cmpfunc);
		clock_t stop2 = clock();
		clock_t stop3 = clock();
		double ellapsed2 = (double)(stop2 - start2) / CLOCKS_PER_SEC;
		double ellapsed3 = (double)(stop3 - start3) / CLOCKS_PER_SEC;
		printf("Presjek sortiranih bez qsorta = %f sec \n", ellapsed2);
		printf("Presjek sortiranih s QSORTOM = %f sec \n", ellapsed3);
		free(niz4);

		free(niz1);
		free(niz2);
		n3 = 0;
		n4 = 0;
		printf("\n");
	}
	printf("\n \n \n");
	printf("Drugi krug__________________________________________________\n \n");
	printf("############ Niz 1 promjenjiv, niz 2 fiksan  ############# \n");
	for (; n1 <= 50000; n1 += 5000)
	{
		printf("Iteracija = %d\n", n1);
		niz1 = generiraj(n1);
		shuffle(niz1, n1);
		niz2 = generiraj(n2);
		shuffle(niz2, n2);

		//IZRACUN DVA NESORITANA

		clock_t start4 = clock();
		niz3 = presjek(niz1, niz2, n1, n2, &n3);
		clock_t stop4 = clock();
		double ellapsed4 = ((double)stop4 - start4) / CLOCKS_PER_SEC;
		printf("Vrijeme presjeka 2 nesortirana niza= %f sec ! \n", ellapsed4);
		free(niz3);

		/// IZRACUN SORTIRANOG I NESORTIRANOG

		clock_t start5 = clock();
		niz4 = presjek_sortirani(niz1, niz2, n1, n2, &n4);
		clock_t start6 = clock();
		qsort(niz2, n2, sizeof(int), cmpfunc);
		clock_t stop5 = clock();
		clock_t stop6 = clock();
		double ellapsed5 = (double)(stop5 - start5) / CLOCKS_PER_SEC;
		double ellapsed6 = (double)(stop6 - start6) / CLOCKS_PER_SEC;
		printf("Presjek sortiranih bez qsorta = %f sec \n", ellapsed5);
		printf("Presjek sortiranih s QSORTOM = %f sec \n", ellapsed6);
		free(niz4);
		free(niz1);
		free(niz2);
		n3 = 0;
		n4 = 0;
		printf("\n");
	}
}