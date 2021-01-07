#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int len = 10000;

typedef struct
{
    void *s;
    int prioritet;
} Element;

typedef struct
{
    Element *niz;
} Red;

void print(Red *red)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d \n", red->niz->prioritet);
    }
}

void zamjeni_elemente(Red *red, int index1, int index2)
{
    Element temp = red->niz[index1];
    red->niz[index1] = red->niz[index2];
    red->niz[index2] = temp;
}
void popravi_prema_vrhu(Red *red, int c)
{
    int ri = floor((c - 1) / 2);
    Element r = red->niz[ri];
    if (r.prioritet < red->niz[c].prioritet)
    {
        zamjeni_elemente(red, ri, c);
        popravi_prema_vrhu(red, ri);
    }
}

void popravi_prema_dnu(Red *red, int r)
{
    int l = 2 * r + 1;
    int d = 2 * r + 2;
    if (d >= len || l >= len)
        return;

    if (red->niz[r].prioritet < red->niz[l].prioritet && red->niz[l].prioritet >= red->niz[d].prioritet)
    {
        zamjeni_elemente(red, r, l);
        popravi_prema_dnu(red, l);
    }
    else if (red->niz[r].prioritet < red->niz[d].prioritet && red->niz[d].prioritet >= red->niz[l].prioritet)
    {
        zamjeni_elemente(red, r, d);
        popravi_prema_dnu(red, d);
    }
}

void ukloni_s_vrha(Red *red)
{
    red->niz[0] = red->niz[len - 1];
    len = len - 1;
    red->niz = (Element *)realloc(red->niz, len * sizeof(Element));
    popravi_prema_dnu(red, 0);
}
void dodaj_na_kraj(Red *red, int c)
{
    red->niz[c].prioritet = rand() % len;
    popravi_prema_vrhu(red, c);
}


int main()
{
    srand(time(NULL));
    Red *red = (Red *)malloc(sizeof(Red));
    red->niz = (Element *)malloc(len * sizeof(Element));
    for (int i = 0; i < len; i++)
    {
        dodaj_na_kraj(red,i);
    }

    printf("-------prije uklanjanja sa vrha-------\n");
    print(red);

    printf("-------poslje uklanjanja sa vrha-------\n");
    ukloni_s_vrha(red);
    print(red);

    free(red->niz);
    free(red);
}