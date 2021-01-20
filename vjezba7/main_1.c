#include <stdio.h>
#include <malloc.h>

typedef struct _Node {
	int broj;
	struct _Node* left;
	struct _Node* right;
} Node;

void print(Node* tree) {
	if (tree == NULL)
		return;
	printf("%d ", tree->broj);
	print(tree->left);
	print(tree->right);
}

int provjeri(Node* tree, int broj) {
	if (tree == NULL)
		return 0;
	if (broj > tree->broj) {
		return provjeri(tree->right, broj);
	}
	if (broj < tree->broj) {
		return provjeri(tree->left, broj);
	}
	return 1;
}

Node* dodaj(Node* tree, int broj) {
	if (tree == NULL) {
		Node* novi = (Node*)malloc(sizeof(Node));
		novi->broj = broj;
		novi->left = NULL;
		novi->right = NULL;
		return novi;
	}

	if (broj > tree->broj) {
		tree->right = dodaj(tree->right, broj);
	}
	else if (broj < tree->broj) {
		tree->left = dodaj(tree->left, broj);
	}
	return tree;
}

int broji(Node* tree) {
	if (tree == NULL)
		return 0;
	// 1 + broj_lijevih + broj_desnih
	int bl = broji(tree->left);
	int br = broji(tree->right);
	return 1 + bl + br;
}

void main() {
	Node* tree = NULL;
	Node a, b, c, d, e, f;

	tree = &a;
	a.broj = 6;
	a.left = &b;
	a.right = &c;
	b.broj = 3;
	b.left = &d;
	b.right = NULL;
	d.broj = 2;
	d.left = NULL;
	d.right = NULL;
	c.broj = 8;
	c.left = &e;
	c.right = &f;
	e.broj = 7;
	e.left = NULL;
	e.right = NULL;
	f.broj = 9;
	f.left = NULL;
	f.right = NULL;

	print(tree);
	printf("\n broj cvorova = %d\n", broji(tree));

	// printf("\n10 -> %d", provjeri(tree, 10));
	// printf("\n7 -> %d", provjeri(tree, 7));

	tree = dodaj(tree, 5);

	print(tree);
	printf("\n broj cvorova = %d\n", broji(tree));
}