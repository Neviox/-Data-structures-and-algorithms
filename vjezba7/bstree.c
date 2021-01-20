#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "bstree.h"

BSTree NewBSTree()
{
	// Novo prazno stablo
	return NULL;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokaziva�.
	if (*bst == NULL)                       //radi novi
	{
		*bst = (BSTree)malloc(sizeof(Node));
		(*bst)->word = word;
		(*bst)->left = NULL;
		(*bst)->right = NULL;
	}
	else if (strcmp((*bst)->word, word) > 0) //ako je rijec manja od trenutne,rekurzivno livo ili desno
	{
		return AddNode(&(*bst)->left, word);
	}
	else if (strcmp((*bst)->word, word) < 0)
	{
		return AddNode(&(*bst)->right, word);
	}
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
	if (bst == NULL)
		return 0;

	int livo = BSTHeight(bst->left);
	int desno = BSTHeight(bst->right);

	if (livo > desno)
		return (livo + 1);
	else
		return (desno + 1);
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rije�i u stablu na ekran po abecednom redu.
	// In-order �etnja po stablu (lijevo dijete, �vor, desno dijete)
	if (bst == NULL)
		return;
	PrintBSTree(bst->left);
	printf("%s \n ", bst->word);
	PrintBSTree(bst->right);
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (ttenutni �vor pa djeca)
	if (bst == NULL)
		return;
	fprintf(fd, "%s ", bst->word); //rijec
	SaveBSTree(bst->left, fd);	   //liva strana
	SaveBSTree(bst->right, fd);	   //desna strana
}

void DeleteBSTree(BSTree bst)
{
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)
	if (bst == NULL)
		return;
	DeleteBSTree(bst->left);
	DeleteBSTree(bst->right);
	printf("Brisanje rijeci - %s \n", bst->word);

	free(bst->word);
	free(bst);
}

BSTree LoadBSTree(FILE *fd)
{
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().
	BSTree bst = NewBSTree();
	char buffer[1024];
	while (readWord(fd, buffer))
	{
		AddNode(&bst, strdup(buffer));
	}
	return bst;
}
