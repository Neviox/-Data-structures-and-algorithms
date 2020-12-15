#ifndef DICTIONARY_H
#define DICTIONARY_H

typedef struct Word {
	char *word; // rijec
	int count; // broj pojavljivanja rijeci
	struct Word *next; 
} Word;

typedef Word* Dictionary;

// kreaira novi prazni rjecnik
Dictionary create(); //rjeseno

// dodaje rijec ili uvecava broj pojavljivanja rijeci u rjecniku
// rijeci se dodaju u abecednom redu
void add(Dictionary dict, char *str);

// ispisuje sve rijeci i broj pojavljivanja svake rijeci
void print(Dictionary dict); //rjeseno

// bri�e cijeli rje�nik
void destroy(Dictionary dict); //rjeseno

Dictionary filterDictionary(Dictionary indict,int (*filter)(Word *w));

int filter(Word *w);

char* najduza(Dictionary dict);
int ukupan_broj_rijeci(Dictionary dict);
void dodaj_na_kraj_liste(Dictionary dict, char *str);

#endif