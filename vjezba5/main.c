#include <stdio.h>
#include <ctype.h>
#include "dictionary.h"
#include "dictionary.c"

int readWord(FILE *fd, char *buffer)
{
	int c;
	
	do {
		c = fgetc(fd);				
		if(c == EOF)
			return 0;
	} while(!isalpha(c));

	do {
		*buffer = tolower(c);
		buffer++;
		c = fgetc(fd);
		if(c == 146)
			c = '\'';
	} while(isalpha(c) || c == '\'');

	*buffer = '\0';
	return 1;
}

void main()
{
	FILE *fd;
	char buffer[1024];
	Dictionary dict;
				
	fd = fopen("liar.txt", "rt");
	if(fd == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	dict = create();
	while(readWord(fd, buffer))
	{
		//printf("%s\n", buffer);
		add(dict, buffer);
	}

	fclose(fd);
	
	//printf("### Add funkcija\n\n");
	//print(dict);

	/*dict = filterDictionary(dict, filter);
	printf("### Filter funckija \n\n");
	print(dict);*/

	//printf("### Destroy \n \n")
	//destroy(dict);
	
	//printf("najduza rijec je %s",najduza(dict));
	//printf("ukupan broj rijeci je %d",ukupan_broj_rijeci(dict));
	char str1[]="kraj";
	char str2[]="pocetak";
	dodaj_na_kraj_liste(dict,str1);
	dodaj_na_pocetak_liste(dict,str2);
	print(dict);
}
