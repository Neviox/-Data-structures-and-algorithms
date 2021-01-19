#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int len = 10;
//int len = 10000;

typedef struct
{
    void *podatak;
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
        printf("%d \n", red->niz[i].prioritet);
    }
}

void zamjena(Red *red, int indexi, int indexj)
{
    Element temp = red->niz[indexi];
    red->niz[indexi] = red->niz[indexj];
    red->niz[indexj] = temp;
}
void fixup(Red *red, int c)
{
    int ri = floor((c - 1) / 2);
    Element r = red->niz[ri];
    if (r.prioritet < red->niz[c].prioritet)
    {
        zamjena(red, ri, c);
        fixup(red, ri);
    }
}

void dodaj(Red *red, int c)
{
    red->niz[c].prioritet = rand() % len;
    fixup(red, c);
}

void fixdown(Red *red, int r)
{
    int l = 2 * r + 1;
    int d = 2 * r + 2;
    if (d >= len || l >= len)
        return;

    if (red->niz[r].prioritet < red->niz[l].prioritet && red->niz[l].prioritet >= red->niz[d].prioritet)
    {
        zamjena(red, r, l);
        fixdown(red, l);
    }
    else if (red->niz[r].prioritet < red->niz[d].prioritet && red->niz[d].prioritet >= red->niz[l].prioritet)
    {
        zamjena(red, r, d);
        fixdown(red, d);
    }
}

void delup(Red *red)
{
    red->niz[0] = red->niz[len - 1];
    len = len - 1;
    red->niz = (Element *)realloc(red->niz, len * sizeof(Element));
    fixdown(red, 0);
}


int main()
{
    srand(time(NULL));
    Red *red = (Red *)malloc(sizeof(Red));
    red->niz = (Element *)malloc(len * sizeof(Element));
    for (int i = 0; i < len; i++)
    {
        dodaj(red,i);
    }

    print(red);

    printf("<-------------!!!!!* Uklanjanje s vrha *!!!!!!-------------->\n");
    delup(red);
    print(red);

    free(red->niz);
    free(red);
}