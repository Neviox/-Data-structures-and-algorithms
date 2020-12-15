#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// kreaira novi prazni rjecnik
Dictionary create()
{
  Dictionary rjecnik = (Dictionary)malloc(sizeof(Word));
  rjecnik->count = 0;
  rjecnik->next = NULL;
  rjecnik->word = NULL;

  return rjecnik;
}
// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char *str)
{

  Dictionary p = dict;
  Dictionary n = dict->next;

  Dictionary novi = (Dictionary)malloc(sizeof(Word));
  novi->word = (char *)malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(novi->word, str);
  novi->count = 1;

  while (n != NULL)
  {
    if (strcmp(n->word, str) == 0)
    { //ako su rijeci iste brojac +1 i oslobadamo rijec iz novog
      n->count++;
      free(novi->word);
      free(novi);
      return;
    }
    else if (n->word == NULL || strcmp(n->word, str) < 0)
    { //ako nisu isti stavi ga abecedno u listi
      novi->next = n;
      p->next = novi;
      return;
    }
    n = n->next; //sljedeci element
    p = p->next;
  }

  p->next = novi; //stavi novi element na kraj
  novi->next = NULL;
}

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict)
{
  dict = dict->next;
  while (dict != NULL)
  { //dok ne dode do kraja liste printaj
    printf("%s - count:%d\n", dict->word, dict->count);
    dict = dict->next;
  }
}
// bri�e cijeli rje�nik
void destroy(Dictionary dict)
{

  Dictionary temp = dict;
  dict = dict->next;
  free(temp);

  while (dict != NULL)
  {                    //dok nije kraj liste
    temp = dict;       //sadasnji spreman u temp
    dict = dict->next; //skoci na sljedeci
    free(temp->word);  //oslobodi rekurzivno temp
    free(temp);
  }
}

Dictionary filterDictionary(Dictionary indict, int (*filter)(Word *w))
{
  Dictionary p = indict;
  Dictionary n = indict->next;

  while (n != NULL)
  {
    if (filter(n) == 1)
    { //ako je zadovoljen filter idemo na sljedeci
      p = p->next;
      n = n->next;
    }
    else
    { //ako nije zadovoljen prosli pokazuje na sljedeci i oslobada se element liste
      p->next = n->next;
      free(n->word);
      free(n);
      n = p->next; // postavlja n na sljedeci
    }
  }
  return indict;
}

int filter(Word *w)
{
  if ((w->count > 5 && w->count < 10) && strlen(w->word) > 3)
  { //broj ponavljanja 5-10 i duljina veca od 3
    return 1;
  }
  else
    return 0;
}
char *najduza(Dictionary dict) //najduza ric
{
  Dictionary n = dict->next;
  char *p = NULL;
  if (n == NULL)
    return p;
  p = n->word;
  n = n->next;
  while (n != NULL)
  {
    if (strlen(n->word) > strlen(p))
    {
      p = n->word;
    }
    n = n->next;
  }
  return p;
}
int ukupan_broj_rijeci(Dictionary dict)
{
  int brojac = 0;
  while (dict != NULL)
  {
    brojac++;
    dict = dict->next;
  }
  return brojac;
}

void dodaj_na_kraj_liste(Dictionary dict, char *str)
{
  Dictionary n=dict->next;
  Dictionary nova=(Dictionary)malloc(sizeof(Word));
  nova->word=(char*)malloc(sizeof(char)*strlen(str)+1);
  nova->count=1;
  while(n!=NULL){
    n=n->next;
    dict=dict->next;
  }
  strcpy(nova->word,str);
  dict->next=nova;
  nova->next=NULL;
}

void dodaj_na_pocetak_liste(Dictionary dict,char* str){
  Dictionary nova=(Dictionary)malloc(sizeof(Word));
  nova->word=(char*)malloc(sizeof(char)*strlen(str)+1);
  Dictionary n=dict->next;
  strcpy(nova->word,str);
  nova->next=dict;
  while(n!=NULL){
     if(strcmp(n->word, str) > 0) break;
    n=n->next;
    
    dict=dict->next;
  }
  
}
  

