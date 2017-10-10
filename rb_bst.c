/**
This program implements the back end of a Binary Search Tree ADT using a
red-black tree structure. The goal is to practice ADT development in c.

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

typedef enum {BLACK='b', RED='r'} color_t;

struct NODE_S{
	Node *right;
	Node *left;
	Node *parent;
	STYPE *data;
	color_t color;
};


static void destroy_node(Node *n){
	free(n->data);
	free(n);
}


static Node* grandparent(Node* n){
	if(n && n->parent){
		return n->parent->parent;
	}
	else{
		return NULL;
	}
}


static Node* uncle(Node* n){
	Node* g = grandparent(n);
	if(!g){
		return NULL;
	}
	if(n->parent == g->left){
		return g->right;
	}
	else{
		return g->left;
	}
}


static Node* sibling(Node* n){
	if((n==NULL) || (n->parent == NULL)){
		return NULL;
	}
	if(n == n->parent->left){
		return n->parent->right;
	}
	else{
		return n->parent->left;
	}
}


static void rotate_right(BstADT* tree, Node* n){
	if(n->parent){
		if(n == n->parent->left){
			n->parent->left = n->left;
			n->left->parent = n->parent;
		}
		else{
			n->parent->right = n->left;
			n->left->parent = n->parent;
		}
	}
	else{
		tree->root = n->left;
		n->left->parent = NULL;
	}
	n->parent = n->left;
	n->left = n->parent->right;
	n->parent->right = n;
}


static void rotate_left(BstADT* tree, Node* n){
	if(n->parent){
		if(n == n->parent->left){
			n->parent->left = n->right;
			n->right->parent = n->parent;
		}
		else{
			n->parent->right = n->right;
			n->right->parent = n->parent;
		}
	}
	else{
		tree->root = n->right;
		n->right->parent = NULL;
	}
	n->parent = n->right;
	n->right = n->parent->left;
	n->parent->left = n;
}


static void insertCase1(BstADT* tree, Node* n);
static void insertCase2(BstADT* tree, Node* n);
static void insertCase3(BstADT* tree, Node* n);
static void insertCase4(BstADT* tree, Node* n);
static void insertCase5(BstADT* tree, Node* n);


static void insertCase1(BstADT* tree, Node* n){
	if((n->parent) == NULL){
		n->color = BLACK;
	}
	else{
		insertCase2(tree, n);
	}
}


static void insertCase2(BstADT* tree, Node* n){
	if(n->parent->color == BLACK){
		return;
	}
	else{
		insertCase3(tree, n);
	}
}


static void insertCase3(BstADT* tree, Node* n){
	Node* u = uncle(n), *g;
	
	if((u != NULL) && (u->color == RED)){
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insertCase1(tree, g);
	}
	else{
		insertCase4(tree, n);
	}
}


static void insertCase4(BstADT* tree, Node* n){
	Node* g = grandparent(n);

	if((n == n->parent->right) && (n->parent == g->left)){
		rotate_left(tree, n->parent);
		n = n->left;
	}
	else if((n == n->parent->left) && (n->parent == g->right)){
		rotate_right(tree, n->parent);
		n = n->right;
	}
	insertCase5(tree, n);
}


static void insertCase5(BstADT* tree, Node* n){
	Node* g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;

	if(n == n->parent->left){
		rotate_right(tree, g);
	}
	else{
		rotate_left(tree, g);
	}
}


static int numChildren(Node* n){
	int c = 0;
	if(n->right){
		c++;
	}
	if(n->left){
		c++;
	}
	return c;
}


static Node* find_successor(Node* n){
	Node* cur = n->right;
	while(cur->left){
		cur = cur->left;
	}
	return cur;
}


static void deleteOneChild(BstADT* tree, Node* n);
static void deleteCase1(BstADT* tree, Node* n);
static void deleteCase2(BstADT* tree, Node* n);
static void deleteCase3(BstADT* tree, Node* n);
static void deleteCase4(BstADT* tree, Node* n);
static void deleteCase5(BstADT* tree, Node* n);
static void deleteCase6(BstADT* tree, Node* n);

static void delete_nod(BstADT* tree, Node* n){
	if(numChildren(n) > 1){
		Node* successor = find_successor(n);
		n->data = successor->data;
		delete_nod(tree, successor);
	}
	else{
		deleteOneChild(tree, n);
	}
}


static void replaceNode(BstADT* tree, Node* n, Node* c){
	if(n->parent){
		if(n == n->parent->left){
			n->parent->left = c;
			c->parent = n->parent;
		}
		else{
			n->parent->right = c;
			c->parent = n->parent;
		}
	}
	else{
		c->parent = NULL;
		tree->root = c;
	}
}


void deleteOneChild(BstADT* tree, Node* n){
	Node* child = NULL;
	if(n->right){
		child = n->right;
	}
	else{
		child = n->left;
	}

	if(child != NULL){
		replaceNode(tree, n, child);
		if(n->color == BLACK){
			if(child->color == RED){
				child->color = BLACK;
			}
			else{
				deleteCase1(tree, child);
			}
		}
		destroy_node(n);
	}
	else{
		if(n->color == BLACK){
			deleteCase1(tree, n);
		}
		if(n->parent){
			if(n == n->parent->left){
				n->parent->left = NULL;
			}
			else{
				n->parent->right = NULL;
			}
		}
		else{
			tree->root = NULL;
		}
		destroy_node(n);
	}
}


static void deleteCase1(BstADT* tree, Node* n){
	if(n->parent != NULL){
		deleteCase2(tree, n);
	}
}


static void deleteCase2(BstADT* tree, Node* n){
	Node* s = sibling(n);

	if(s->color == RED){
		n->parent->color = RED;
		s->color = BLACK;
		if(n == n->parent->left){
			rotate_left(tree, n->parent);
		}
		else{
			rotate_right(tree, n->parent);
		}
	}
	deleteCase3(tree, n);
}


static void deleteCase3(BstADT* tree, Node* n){
	Node* s = sibling(n);

	if((n->parent->color == BLACK) && (s->color == BLACK)){
		if((s->left == NULL) || (s->left->color == BLACK)){
			if((s->right == NULL) || (s->right->color == BLACK)){
				s->color = RED;
				deleteCase1(tree, n->parent);
			}
			else{
				deleteCase4(tree, n);
			}
		}
		else{
			deleteCase4(tree, n);
		}
	}
	else{
		deleteCase4(tree, n);
	}
}


static void deleteCase4(BstADT* tree, Node* n){
	Node* s = sibling(n);

	if((n->parent->color == RED) &&
		(s->color == BLACK) &&
		(s->left == NULL || s->left->color == BLACK) &&
		(s->right == NULL || s->right->color == BLACK)){
		s->color = RED;
		n->parent->color = BLACK;
	}
	else{
		deleteCase5(tree, n);
	}
}


static void deleteCase5(BstADT* tree, Node* n){
	Node *s = sibling(n);

	if(s->color == BLACK){
		if((n == n->parent->left) &&
			(s->right->color == BLACK) &&
			(s->left->color == RED)){
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(tree, s);
		}
		else if((n == n->parent->right) &&
				(s->left->color == BLACK) &&
				(s->right->color == RED)){
				s->color = RED;
				s->right->color = BLACK;
				rotate_left(tree, s);
		}
	}
	deleteCase6(tree, n);
}


static void deleteCase6(BstADT* tree, Node* n){
	Node* s = sibling(n);

	s->color = n->parent->color;
	n->parent->color = BLACK;

	if(n == n->parent->left){
		s->right->color = BLACK;
		rotate_left(tree, n->parent);
	}
	else{
		s->left->color = BLACK;
		rotate_right(tree, n->parent);
	}
}


BstADT* tree_create(void){
	BstADT* tree = malloc(sizeof(BstADT));
	*tree = (BstADT){NULL};
	return tree;
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


static void add_node(BstADT* tree, Node** loc, tdata_t* n){
	if(*loc){
		int diff = compare((*loc)->data, n);
		if(diff > 0){
			if((*loc)->right){
				add_node(tree, &((*loc)->right), n);
			}
			else{
				Node* new = malloc(sizeof(Node));
				*new = (Node){.data = n, .parent = (*loc), .left = NULL, .right = NULL, .color = RED};
				(*loc)->right = new;
				insertCase1(tree, new);
			}
		}
		else if(diff < 0){
			if((*loc)->left){
				add_node(tree, &((*loc)->left), n);
			}
			else{
				Node* new = malloc(sizeof(Node));
				*new = (Node){.data = n, .parent = (*loc), .left = NULL, .right = NULL, .color = RED};
				(*loc)->left = new;
				insertCase1(tree, new);
			}
		}
	}
	else{
		Node* new = malloc(sizeof(Node));
		*new = (Node){.data = n, .parent = NULL, .left = NULL, .right= NULL, .color = RED};
		(*loc) = new;
		insertCase1(tree, *loc);
	}
}

void tree_add(BstADT* tree, tdata_t* n){
	add_node(tree, &(tree->root), n);
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


static void deleteNode(BstADT* tree, tdata_t* n, Node** loc){
	if(*loc){
		int diff = compare((*loc)->data, n);
		if(diff > 0){
			if((*loc)->right){
				deleteNode(tree, n, &((*loc)->right));
			}
		}
		else if(diff < 0){
			if((*loc)->left){
				deleteNode(tree, n, &((*loc)->left));
			}
		}
		else{
			delete_nod(tree, *loc);
		}
	}
}


void tree_remove(BstADT* tree, tdata_t* n){
	deleteNode(tree, n, &(tree->root));
}


static void print_node(Node* n, Traversal trav){
	if(n){
		switch(trav){
			case PREORDER:
				printf("Found: ");
				print(n->data);
				printf(" (%c)\n", n->color);
				print_node(n->left, trav);
				print_node(n->right, trav);
				break;
			case INORDER:
				print_node(n->left, trav);
				printf("Found: ");
				print(n->data);
				printf(" (%c)\n", n->color);
				print_node(n->right, trav);
				break;
			case POSTORDER:
				print_node(n->left, trav);
				print_node(n->right, trav);
				printf("Found: ");
				print(n->data);
				printf(" (%c)\n", n->color);
				break;
		}
	}
}

void print_tree(BstADT* tree, Traversal trav){
	print_node(tree->root, trav);
}
