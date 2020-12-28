#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>

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
    else if (n->word == NULL || strcmp(n->word, str) > 0)
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
  Dictionary n = dict->next;
  Dictionary nova = (Dictionary)malloc(sizeof(Word));
  nova->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  nova->count = 1;
  while (n != NULL)
  {
    n = n->next;
    dict = dict->next;
  }
  strcpy(nova->word, str);
  dict->next = nova;
  nova->next = NULL;
}

void dodaj_na_pocetak_liste(Dictionary dict, char *str)
{
  Dictionary nova = (Dictionary)malloc(sizeof(Word));
  nova->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  Dictionary n = dict->next;
  strcpy(nova->word, str);
  nova->next = dict;
  while (n != NULL)
  {
    if (strcmp(n->word, str) > 0)
      break;
    n = n->next;

    dict = dict->next;
  }
}
void add_word(Dictionary dict, char *str)
{
  Dictionary n = dict->next;
  Dictionary nova = (Dictionary)malloc(sizeof(Word));
  nova->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  strcpy(nova->word, str);
  nova->count = 1;
  nova->next = dict->next;
  dict->next = nova;
}
char *longest_word(Dictionary dict)
{
  dict = dict->next;
  char *temp = dict->word;
  while (dict != NULL)
  {
    if (strlen(dict->word) > strlen(temp))
    {
      temp = dict->word;
    }
    dict = dict->next;
  }
  return temp;
}
int word_sum(Dictionary dict)
{
  int wordsum = 0;
  while (dict != NULL)
  {
    wordsum += dict->count;
    dict = dict->next;
  }
  return wordsum;
}
void delete_before_element(Dictionary dict, char *str)
{
  Dictionary novi = (Dictionary)malloc(sizeof(Word));
  novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  novi->count = 1;
  char test[] = "youngest";
  strcpy(novi->word, str);
  Dictionary n = dict->next;
  Dictionary p = dict;
  while (n != NULL)
  {
    if (strcmp(n->word, test) == 0)
    {
      novi->next = n;
      dict->next = novi;
    }
    n = n->next;
    dict = dict->next;
  }
}
void insert(Dictionary dict, char *str, int index)
{
  Dictionary novi = (Dictionary)malloc(sizeof(Word));
  novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  novi->count = 1;
  strcpy(novi->word, str);
  Dictionary n = dict->next;
  int brojac = 0;
  while (n != NULL)
  {
    if (brojac == index)
    {
      novi->next = n;
      dict->next = novi;
    }
    brojac++;
    n = n->next;
    dict = dict->next;
  }
}
void delete_first(Dictionary dict)
{
  Dictionary temp = dict->next;
  Dictionary n = dict->next->next;
  dict->next = n;
  free(temp->word);
  free(temp);
}
// void delete_last(Dictionary dict){
//     Dictionary n=dict->next;
// do{
//     n=dict;
//     dict=dict->next;
//     if(dict->next==NULL){
//         n->next=NULL;
//         free(dict->next);
//         }
//     }
//     while(n->next!=NULL);
// };
void delete_word(Dictionary dict, char *str)
{
  Dictionary p = dict;
  dict = dict->next;
  Dictionary n = dict->next;
  while (n != NULL)
  {
    if (strcmp(n->word, str) == 0)
    {
      p->next = p->next->next;
      free(n->word);
    }
    p = p->next;
    n = n->next;
  }
}
void brisi_zadnji(Dictionary dict)
{
  dict = dict->next;
  Dictionary n = dict->next;
  Dictionary p = dict;
  while (n->next != NULL)
  {
    n = n->next;
    p = p->next;
  }
  p->next = NULL;
  free(n->word);
  free(n);
}

void okreni_listu(Dictionary dict)
{
  Dictionary p = dict->next;
  Dictionary n = dict->next->next;
  Dictionary tmp = n;
  p->next = NULL;
  while (tmp != NULL)
  {
    tmp = tmp->next;
    n->next = p;
    p = n;
    n = tmp;
  }
  dict->next = p;
}
void delete_with_more_than10(Dictionary dict)
{
  Dictionary p, temp = dict;
  while (temp->next != NULL)
  {
    if (strlen(temp->next->word) > 4)
    {
      p = temp->next->next;
      free(temp->next->word);
      free(temp->next);
      temp->next = p;
    }
    else
    {
      temp = temp->next;
    }
  }
}
void swap_first_last(Dictionary dict)
{
  Dictionary dummy = dict;
  Dictionary prvi = dict->next;
  Dictionary n = prvi->next;
  Dictionary p = prvi;
  while (n->next != NULL)
  {
    n = n->next;
    p = p->next;
  }
  Dictionary zadnji = n;
  dummy->next = n;      //dummy u zadnji
  n->next = prvi->next; //zadnji u 2.
  p->next = prvi;       //predzadnji u 1.
  prvi->next = NULL;    // prvi(zadnji)u NULL;
}

void dodavanje_ispred_10(Dictionary dict, char *str)
{
  Dictionary p = dict;
  Dictionary n = dict->next;
  Dictionary novi = (Dictionary)malloc(sizeof(Word));
  novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  strcpy(novi->word, str);
  novi->count = 1;
  while (n != NULL)
  {
    if (strlen(n->word) > 8)
    {
      Dictionary novi = (Dictionary)malloc(sizeof(Word));
      novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
      strcpy(novi->word, str);
      novi->count = 1;
      p->next = novi;
      novi->next = n;
      p = p->next->next;
      n = n->next;
    }
    n = n->next;
    p = p->next;
  }
}
//prima dva stringa i stavlja ih u listu iza prvog elementa
void prebacivanje_u_novu(Dictionary dict)
{
  Dictionary n = dict->next;
  Dictionary p = dict;
  Dictionary dict2 = (Dictionary)malloc(sizeof(Word));
  Dictionary temp = dict2;
  while (n != NULL)
  {
    if (strlen(n->word) > 5)
    {
      p->next = n->next;
      temp->next = n;
      temp = n;
      n = p->next;
    }
    n = n->next;
    p = p->next;
  }
  print(dict2);
}

//p=dict , n=dict.next ,temp kad brises i kad dodajes u novu
//kad brises prvo p.next je n.next(spona na sljedeci element);;;;2. free(n);;;3. n=p.next (jer n vise ne postoji)

/*void prebacivanje_niza_u_listu(Dictionary dict,char* niz){
  Dictionary novi=(Dictionary)malloc(sizeof(Word));
  Dictionary p = dict;
  while(p->next!=NULL){
    p=p->next;
  }
  for(int i=0;i<5;i++){
    novi->word=niz[i];
    p->next=novi;
    p=novi;
  }
  p->next=NULL;
}

void dodaj_na_karj(Dictionary dict, char* str)
{
	Dictionary temp = dict, novi = (Word*)malloc(sizeof(Word));
	novi->word = strdup(str);
	novi->count = 1;
	novi->next = NULL;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = novi;
	return;
}
//RADI
void brisanje_nakraju(Dictionary dict)
{
	Dictionary sljedeci, temp = dict;
	while (temp->next->next != NULL)
	{
		temp = temp->next;
	}
	free(temp->next->word);
	free(temp->next);
	temp->next = NULL;
}
//RADI
void brisanje_odredenog_elemenata(Dictionary dict, char* element) {
	Dictionary novi, temp = dict;
	while (temp->next!=NULL)
	{
		if (strcmp(temp->next->word, element) == 0) {
			novi = temp->next->next;
			free(temp->next->word);
			free(temp->next);
			temp->next= novi;
			return;
		}
		else {
			temp = temp->next;
		}
	}
	if (temp->next == NULL) {
		printf("*******************************************\n\n");
		printf("Trazena rijec za uklanjanje nepostoji!\n");
		printf("\n\n");
		printf("*******************************************\n\n");
		return;
	}
}
//RADI
Dictionary najdulja_rijec(Dictionary dict)
{
	Dictionary najdulja = dict, temp = dict;
	while (temp->next != NULL)
	{
		if (strlen(temp->word) > strlen(najdulja->word))
		{
			najdulja = temp;
		}
		temp = temp->next;
	}
	return najdulja;
}
//RADI
Dictionary dodaj_na_glavu(Dictionary dict, char* str)
{
	Dictionary novi = (Word*)malloc(sizeof(Word));
	novi->word = strdup(str);
	novi->count = 1;
	novi->next = dict;
	return novi;
}
//RADI
Dictionary brisanje_glavu(Dictionary dict)
{
	Dictionary sljedeci;
	sljedeci = dict->next;
	free(dict->word);
	free(dict);
	dict = sljedeci;
	return dict;
}
//radi
void dodavanje_prije_odredenog_indeks(Dictionary dict, int indeks, char* str)
{
	Dictionary temp = dict, novi = (Word*)malloc(sizeof(Word));
	novi->word = strdup(str);
	novi->next = NULL;
	novi->count = 1;
	int i = 0;
	while (i + 1 != indeks)
	{
		i++;
		temp = temp->next;
	}
	novi->next = temp->next;
	temp->next = novi;
	return;
}
//Radi
Dictionary obrnuta_lista(Dictionary dict) {
	Dictionary obrnuta_lista = NULL,temp;
	while (dict->next != NULL) {
		temp = dict;
		dict = dict->next;
		temp->next = obrnuta_lista;
		obrnuta_lista = temp;
	}
	return obrnuta_lista;
}
//RADI
void brisanje_pod_odredenim_uvjetima(Dictionary dict) {
	Dictionary novi, temp = dict;
	while (temp->next != NULL) {
		if (strlen(temp->next->word) > 3) {
			novi = temp->next->next;
			free(temp->next->word);
			free(temp->next);
			temp->next = novi;
		}
		else {
			temp = temp->next;
		}
	}
}

//radi
void kopirani_elemnti_nova_lista(Dictionary kopirani_list,Dictionary dict, int koliko_kopirati) {
	Dictionary temp = dict->next, nova_lista = kopirani_list,novi;
	int i = 0;
	while (i < koliko_kopirati) {
		novi = (Word*)malloc(sizeof(Word));
		novi->word = strdup(temp->word);
		novi->count = temp->count;
		novi->next = NULL;
		while (nova_lista->next != NULL) {
			nova_lista = nova_lista->next;
		}
		nova_lista->next = novi;
		temp = temp->next;
		i++;
	}
}
//RADi
void zamjena_prvi_zdanji(Dictionary dict) {
	Dictionary temp = dict, prvi = dict->next,setac=prvi->next,prijesetac=prvi,zadnji;
	while (setac->next != NULL) {
		setac = setac->next;
		prijesetac = prijesetac->next;
	}
	zadnji = setac;
	temp->next = setac;
	setac->next = prvi->next;
	prijesetac->next = prvi;
	prvi->next = NULL;
}
//radi
void lista_sa_odrdedenim_rjecima(Dictionary dict,Dictionary nova_lista) {
	Dictionary temp = dict, novi_lista=nova_lista,novi;
	while (temp->next != NULL) {
		novi = (Word*)malloc(sizeof(Word));
		novi->word = strdup(temp->word);
		novi->count = 1;
		novi->next = NULL;
		if (strlen(temp->word) > 10) {
			while (novi_lista->next != NULL) {
				novi_lista = novi_lista->next;
			}
			novi_lista->next = novi;
		}
		temp = temp->next;
	}
}*/

void brisanje_prve_2_rici(Dictionary dict)
{
  Dictionary p = dict;
  Dictionary n = dict->next;
  Dictionary temp = dict->next;
  dict->next = dict->next->next;
  free(temp->word);
  free(temp);
  temp = dict->next;
  dict->next = dict->next->next;
  free(temp->word);
  free(temp);
}

/*void zamjena_5_i_50(Dictionary dict)
{
  Dictionary p = dict;
  Dictionary n = dict->next;
  Dictionary p5=NULL, n5=NULL, p50=NULL, n50=NULL, temp;
  int brojac = 0;
  while (n->next != NULL)
  {
    if (brojac == 5)
    {
      n5 = n;
      p5 = p;
      p = p->next;
      n = n->next;
      brojac++;
    }
    if (brojac == 50)
    {
      p50 = p;
      n50 = n;
      p = p->next;
      n = n->next;
    }

    n = n->next;
    p = p->next;
    brojac++;
  }
    p5->next = n50;
    n50->next = n5->next;
    p50->next = n5;
    n5->next = p50->next->next;

  while (n != NULL)
  {
    p = p->next;
    n = n->next;
  }
  return dict;
}*/
/*void dodavanje_ispred_10(Dictionary dict, char *str)
{
  Dictionary p = dict;
  Dictionary n = dict->next;
  Dictionary novi = (Dictionary)malloc(sizeof(Word));
  novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
  strcpy(novi->word, str);
  novi->count = 1;
  while (n != NULL)
  {
    if (strlen(n->word) > 8)
    {
      Dictionary novi = (Dictionary)malloc(sizeof(Word));
      novi->word = (char *)malloc(sizeof(char) * strlen(str) + 1);
      strcpy(novi->word, str);
      novi->count = 1;
      p->next = novi;
      novi->next = n;
      p = p->next->next;
      n = n->next;
    }
    n = n->next;
    p = p->next;
  }
}*/


void obrana(Dictionary dict)
{
  Dictionary p = dict;
  Dictionary n = dict->next;
  Dictionary najduza,pn;
  Dictionary dummy=dict;
  Dictionary prvi=dict->next;
  int brojac=0;
  
  while(n!=NULL){
    if(strlen(n->word)>brojac){
      najduza=n;
      pn=p;
      brojac=strlen(n->word);
    }
  p=p->next;
  n=n->next;
  }
  printf("%s    %s     %d   %s\\\n",najduza->word,pn->word,brojac,prvi->word);
  pn->next=pn->next->next;
  dummy->next=najduza;
  najduza->next=prvi;
  
  
  
}