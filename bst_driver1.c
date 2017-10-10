/**
This program is a simple driver for a Binary Search Tree. It was developed
to practice with ADT development in c.

@author Andrew Searns <abs2157@rit.edu>
*/

#include <stdlib.h>
#include <stdio.h>
#include "type.h"
#include "bstADT.h"

extern int ORD;

int main(void){
	int x = 32;
	int y = 100;
	char c = 'A';
	char d = 'F';
	float f = 3.14;
	float g = -2.0;
	
	STYPE* first = create((data_d)x, INT);
	STYPE* second = create((data_d)y, INT);
	STYPE* third = create((data_d)c, CHAR);
	STYPE* fourth = create((data_d)d, CHAR);
	STYPE* fifth = create((data_d)f, FLOAT);
	STYPE* sixth = create((data_d)g, FLOAT);

	BstADT* tree = tree_create();
	tree_add(tree, first);
	tree_add(tree, second);
	tree_add(tree, third);
	tree_add(tree, fourth);
	tree_add(tree, fifth);
	tree_add(tree, sixth);

	print_tree(tree, PREORDER);
	printf("\n");
	print_tree(tree, INORDER);
	printf("\n");
	print_tree(tree, POSTORDER);

	tree_destroy(tree);

	return 0;
}
/*
tree_create
tree_destroy
tree_add
tree_contains
tree_remove	
*/
