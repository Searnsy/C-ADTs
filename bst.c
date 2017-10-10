/**
This program implements the back end of a Binary Search Tree ADT using a
simple tree structure. The goal is to practice ADT development in c.

@author Andrew Searns <abs2157@rit.edu>
*/

#include <stdlib.h>
#include <stdio.h>
#include "type.h"

typedef struct BST_S BstADT;
typedef struct NODE_S Node;

#define _BST_IMPL_
#include "bstADT.h"

struct BST_S{
	Node *root;
};

struct NODE_S{
	Node *right;
	Node *left;
	Node *parent;
	STYPE *data;
	
};


BstADT* tree_create(void){
	BstADT* tree = malloc(sizeof(BstADT));
	*tree = (BstADT){NULL};
	return tree;
}


static void destroy_node(Node* n){
	destroy_data(n->data);
	free(n);
}

static void destroy_tree(Node* n){
	if(n == NULL)
		return;
	destroy_tree(n->right);
	destroy_tree(n->left);
	destroy_node(n);
}

void tree_destroy(BstADT* tree){
	destroy_tree(tree->root);
	free(tree);
}


static void add_node(Node* cur, tdata_t* n){
	int diff = compare(cur->data, n);
	if(diff > 0){
		if(cur->right != NULL){
			add_node(cur->right, n);
		}
		else{
			Node* new = malloc(sizeof(Node));
			*new = (Node){NULL, NULL, cur, n};
			cur->right = new;
		}
	}
	else if(diff < 0){
		if(cur->left != NULL){
			add_node(cur->left, n);
		}
		else{
			Node* new = malloc(sizeof(Node));
			*new = (Node){NULL, NULL, cur, n};
			cur->left = new;
		}
	}
}			
		

void tree_add(BstADT* tree, tdata_t* n){
	if(tree->root != NULL){
		add_node(tree->root, n);
	}
	else{
		Node* new = malloc(sizeof(Node));
		*new = (Node){NULL, NULL, NULL, n};
		tree->root = new;
	}	
}


static Node* contains_node(Node* cur, tdata_t* n){
	if(cur == NULL){
		return NULL;
	}
	int diff = compare(cur->data, n);
	if(diff == 0){
		return cur;
	}
	if(diff > 0){
		return contains_node(cur->right, n);
	}
	else{
		return contains_node(cur->left, n);
	}
}

int tree_contains(BstADT* tree, tdata_t* n){
	return contains_node(tree->root, n) != NULL;
}

static void remove_node(BstADT* tree, Node* cur, tdata_t* n){
	if(tree->root == NULL){
		return;
	}
	Node* del;
	if(cur != NULL){
		del = cur;
	}
	else{
		del = contains_node(tree->root, n);
	}
	if(del->right == NULL){
		if(del->left == NULL){
			//DEL is a leaf
			if(del->parent == NULL){//DEL is the only node in the tree
				tree_destroy(tree);
			}
			else if(del == del->parent->left){
				del->parent->left = NULL;
				destroy_node(del);
			}
			else{
				del->parent->right = NULL;
				destroy_node(del);
			}
		}
		else{
			 if(del->parent == NULL){
				tree->root = del->left;
				destroy_node(del);
			}
			else{
				if(del == del->parent->left){
					del->parent->left = del->left;
					destroy_node(del);
				}
				else{
					del->parent->right = del->left;
					destroy_node(del);
				}
			}
		}
	}
	else{
		if(del->left == NULL){
			if(del->parent == NULL){
				tree->root = del->right;
				destroy_node(del);
			}
			else{
				if(del == del->parent->left){
					del->parent->left = del->right;
					destroy_node(del);
				}
				else{
					del->parent->right = del->right;
					destroy_node(del);
				}
			}
		}
		else{
			Node* next = del->right;
			while(next->left){
				next = next->left;
			}
			del->data = next->data;
			remove_node(tree, next, n);
		}
	}		
}

void tree_remove(BstADT* tree, tdata_t* n){
	remove_node(tree, NULL, n);
}

void print_node(Node* n, Traversal trav){
	if(n == NULL){
		return;
	}
	switch(trav){
		case PREORDER:
			printf("Found: ");
			print(n->data);
			printf("\n");
			print_node(n->left, trav);
			print_node(n->right, trav);
			break;
		case INORDER:
			print_node(n->left, trav);
			printf("Found: ");
			print(n->data);
			printf("\n");
			print_node(n->right, trav);
			break;
		case POSTORDER:
			print_node(n->left, trav);
			print_node(n->right, trav);
			printf("Found: ");
			print(n->data);
			printf("\n");
			break;
	}
}

void print_tree(BstADT* tree, Traversal trav){
	printf("I'm printing.\n");
	print_node(tree->root, trav);
}
