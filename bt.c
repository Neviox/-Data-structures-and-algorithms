#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int NIZLEN = 10000;
int HEAPLEN = 10;

typedef struct {
  void *s;
  int prioritet;
} Element;

typedef struct {
  Element *niz;
} Red;

void printaj_red(Red *red) {
  for(int i = 0; i < NIZLEN; i++) {
    printf("%d\n", red->niz[i].prioritet);
  }
}

void zamijeni_elemente_u_redu(Red *red, int index1, int index2) {
  Element tmp = red->niz[index1];
  red->niz[index1] = red->niz[index2];
  red->niz[index2] = tmp;

}

void popravi_prema_vrhu(Red *red, int i) {

  if(i == 0) return;
  int parent_index = floor((i-1)/2);
  Element parent = red->niz[parent_index];
  if(parent.prioritet < red->niz[i].prioritet) {
    zamijeni_elemente_u_redu(red, parent_index, i);
    popravi_prema_vrhu(red, parent_index);
  }
}

void dodaj_novi_na_kraj_niza(Red *red, int i) {

  red->niz[i].prioritet = rand()%NIZLEN;
  popravi_prema_vrhu(red, i);

}

void popravi_gomilu_prema_dnu(Red *red, int r) {

  int l = 2*r + 1;
  int d = 2*r + 2;
  if(d >= NIZLEN || l >= NIZLEN) return;

  if(red->niz[r].prioritet < red->niz[l].prioritet && red->niz[l].prioritet >= red->niz[d].prioritet) {
    zamijeni_elemente_u_redu(red, r, l);
    popravi_gomilu_prema_dnu(red, l);
  }
  else if(red->niz[r].prioritet < red->niz[d].prioritet && red->niz[d].prioritet >= red->niz[l].prioritet) {
    zamijeni_elemente_u_redu(red, r, d);
    popravi_gomilu_prema_dnu(red, d);
  }
}

void ukloni_sa_vrha_gomile(Red *red) {

  red->niz[0] = red->niz[NIZLEN-1];
  NIZLEN = NIZLEN -1;
  red->niz = (Element*)realloc(red->niz, NIZLEN*sizeof(Element));
  popravi_gomilu_prema_dnu(red, 0);
}

//dodatno: implementacija heaptsorta

void print_niz(int *niz, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d\n", niz[i]);
    }
}

void zamijeni_elemente_u_nizu(int *niz, int index1, int index2) {
    int tmp = niz[index1];
    niz[index1] = niz[index2];
    niz[index2] = tmp;
}

void heapify(int *niz, int r, int n) {
    int l = 2*r + 1;
    int d = 2*r + 2;

    //zamijena sa lijevim elementom
    if((l < n && d >= n && niz[l] > niz[r]) || (l < n && d < n && niz[l] >= niz[d] && niz[l] > niz[r])) {
        zamijeni_elemente_u_nizu(niz, r, l);
        heapify(niz, l, n);

    //zamijena s desnim elementom
    } else if((d < n && l >= n && niz[d] > niz[r]) || (d < n && l < n && niz[d] >= niz[l] && niz[d] > niz[r])) {
        zamijeni_elemente_u_nizu(niz, r, d);
        heapify(niz, d, n);
    }
}

void napravi_gomilu(int *niz, int n)  {
    int start_index = floor(n/2);
    for(int i = start_index; i >= 0; i--) {
        heapify(niz, i, n);
    }
}

void heapsort(int *niz, int n) {
    if(n == 0) return;
    zamijeni_elemente_u_nizu(niz, 0, n-1);
    heapify(niz, 0, n-1);
    heapsort(niz, n-1);
}

int main() {
  srand(time(NULL));
  Red *red = (Red*)malloc(sizeof(Red));
  red->niz = (Element*)malloc(NIZLEN * sizeof(Element));
  for(int i = 0; i < NIZLEN; i++) {
    dodaj_novi_na_kraj_niza(red, i);
  }

  printf("-------prije uklanjanja sa vrha-------\n");
  printaj_red(red);

  printf("-------poslje uklanjanja sa vrha-------\n");
  ukloni_sa_vrha_gomile(red);
  printaj_red(red);

  free(red->niz);
  free(red);
}

