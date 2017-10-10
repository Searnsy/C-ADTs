#include <stdio.h>
#include <stdlib.h>
#include "redblack.h"


static TreeNode_t **root;


/**
Functions to find a grandparent, uncle, and sibling of a
node. Returns NULL if none exists.

@param n a node to look from
@returns The corresponding node from the tree or NULL
*/
TreeNode_t *grandparent(TreeNode_t *n){
	if(n && n->parent){
		return n->parent->parent;
	}
	else{
		return NULL;
	}
}


/**
Functions to find a grandparent, uncle, and sibling of a
node. Returns NULL if none exists.

@param n a node to look from
@returns The corresponding node from the tree or NULL
*/
TreeNode_t *uncle(TreeNode_t *n){
	TreeNode_t *g = grandparent(n);
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


/**
Functions to find a grandparent, uncle, and sibling of a
node. Returns NULL if none exists.

@param n a node to look from
@returns The corresponding node from the tree or NULL
*/
TreeNode_t *sibling(TreeNode_t *n){
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


/**
Performs the corresponding tree rotation on the tree.

@param the node to rotate from
*/
void rotate_right(TreeNode_t *n){
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
		*root = n->left;
		n->left->parent = NULL;
	}
	n->parent = n->left;
	n->left = n->parent->right;
	n->parent->right = n;
}


/**
Performs the corresponding tree rotation on the tree.

@param the node to rotate from
*/
void rotate_left(TreeNode_t *n){
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
		*root = n->right;
		n->right->parent = NULL;
	}
	n->parent = n->right;
	n->right = n->parent->left;
	n->parent->left = n;
}


/**
Red-Black Tree Insertion Cases:
1) At the root
2) Black Parent
3) Red Parent + Uncle
4) Red Parent, Black Uncle (Node value is between Grandparent and Parent)
5) Red Parent, Black Uncle (Ancestry tree is all lefts or rights through Grandparent)

@param n the node being updated
*/
void insertCase1(TreeNode_t *n){
	if((n->parent) == NULL){
		n->color = BLACK;
	}
	else{
		insertCase2(n);
	}
}


/**
Red-Black Tree Insertion Cases:
1) At the root
2) Black Parent
3) Red Parent + Uncle
4) Red Parent, Black Uncle (Node value is between Grandparent and Parent)
5) Red Parent, Black Uncle (Ancestry tree is all lefts or rights through Grandparent)

@param n the node being updated
*/
void insertCase2(TreeNode_t *n){
	if(n->parent->color == BLACK){
		return;
	}
	else{
		insertCase3(n);
	}
}


/**
Red-Black Tree Insertion Cases:
1) At the root
2) Black Parent
3) Red Parent + Uncle
4) Red Parent, Black Uncle (Node value is between Grandparent and Parent)
5) Red Parent, Black Uncle (Ancestry tree is all lefts or rights through Grandparent)

@param n the node being updated
*/
void insertCase3(TreeNode_t *n){
	TreeNode_t *u = uncle(n), *g;

	if((u != 0) && (u->color == RED)){
		n->parent->color = BLACK;
		u->color = BLACK;
		g = grandparent(n);
		g->color = RED;
		insertCase1(g);
	}
	else{
		insertCase4(n);
	}
}


/**
Red-Black Tree Insertion Cases:
1) At the root
2) Black Parent
3) Red Parent + Uncle
4) Red Parent, Black Uncle (Node value is between Grandparent and Parent)
5) Red Parent, Black Uncle (Ancestry tree is all lefts or rights through Grandparent)

@param n the node being updated
*/
void insertCase4(TreeNode_t *n){
	TreeNode_t *g = grandparent(n);

	if((n == n->parent->right) && (n->parent == g->left)){
		rotate_left(n->parent);
		n = n->left;
	}
	else if((n == n->parent->left) && (n->parent == g->right)){
		rotate_right(n->parent);
		n = n->right;
	}
	insertCase5(n);
}


/**
Red-Black Tree Insertion Cases:
1) At the root
2) Black Parent
3) Red Parent + Uncle
4) Red Parent, Black Uncle (Node value is between Grandparent and Parent)
5) Red Parent, Black Uncle (Ancestry tree is all lefts or rights through Grandparent)

@param n the node being updated
*/
void insertCase5(TreeNode_t *n){
	TreeNode_t *g = grandparent(n);

	n->parent->color = BLACK;
	g->color = RED;

	if(n == n->parent->left){
		rotate_right(g);
	}
	else{
		rotate_left(g);
	}
}

/**
Traverses through the tree and prints according to the traversal type.
This will print a subtree from n.

@param n the root node to start from
@param type The Traversal type to perform
*/
void printTree(TreeNode_t *n, Traversal type){
	if(n){
		switch(type){
			case PREORDER:
				printf("%d, %c\n", n->data, n->color);
				printTree(n->left, type);
				printTree(n->right, type);
				break;
			case INORDER:
				printTree(n->left, type);
				printf("%d\n", n->data);
				printTree(n->right, type);
				break;
			case POSTORDER:
				printTree(n->left, type);
				printTree(n->right, type);
				printf("%d\n", n->data);
				break;
		}
	}
}


/**
Gets the number of non-leaf children (non NULL in this impementation)
of a node.

@param n a node in the tree
@returns the number of non NULL children of n
*/
int numChildren(TreeNode_t *n){
	int c = 0;
	if(n->right){
		c++;
	}
	if(n->left){
		c++;
	}
	return c;
}


/**
Finds the immediate successor in the tree for the given node.
(Minimum value of node->right subtree).

@param n a node in the tree
@returns a pointer to the immediate successor
*/
TreeNode_t *findSuccessor(TreeNode_t *n){
	TreeNode_t *cur = n->right;
	while(cur->left){
		cur = cur->left;
	}
	return cur;
}


/**
Recursively swaps successor data with the node to delete
until the new node to delete has at most one non-leaf child.

(This should only ever run one loop as findSuccessor finds the
first node in the leftmost path of the right subtree that has a
NULL left child (i.e. a leaf node child)

@param n The current node to be deleted
*/
void deleteNod(TreeNode_t *n){
	if(numChildren(n) > 1){
		TreeNode_t *successor = findSuccessor(n);
		n->data = successor->data;
		deleteNod(successor);
	}
	else{
		deleteOneChild(n);
	}
}


/**
Inserts node c into the location of the tree where node n is.
This process removes n from the tree and also updates the root
pointer if necessary.

This is the first step to delete a Black node with a Black child
node.

@param n the node to be deleted from the tree
@param c the non NULL child node of n
*/
void replaceNode(TreeNode_t *n, TreeNode_t *c){
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
		*root = c;
	}
}


/**
Deletes node n from the Red-Black tree. In the non-trivial
case where n and its child are Black, it calls the deleteCase
sequence.

@param n the node to be removed from the tree
*/
void deleteOneChild(TreeNode_t *n){
	TreeNode_t *child = NULL;
	if(n->right){
		child = n->right;
	}
	else{
		child = n->left;
	}
	
	if(child != NULL){
		replaceNode(n, child);
		if(n->color == BLACK){
			if(child->color == RED){
				child->color = BLACK;
			}
			else{
				deleteCase1(child);
			}
		}
		free(n);
	}
	else{
		if(n->color == BLACK){
			deleteCase1(n);
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
			*root = NULL;
		}
		free(n);
	}
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase1(TreeNode_t *n){
	if(n->parent != NULL){
		deleteCase2(n);
	}
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase2(TreeNode_t *n){
	TreeNode_t *s = sibling(n);

	if(s->color == RED){
		n->parent->color = RED;
		s->color = BLACK;
		if(n == n->parent->left){
			rotate_left(n->parent);
		}
		else{
			rotate_right(n->parent);
		}
	}
	deleteCase3(n);
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase3(TreeNode_t *n){
	TreeNode_t *s = sibling(n);

	if((n->parent->color == BLACK) && (s->color == BLACK)){
		if((s->left == NULL) || (s->left->color == BLACK)){
			if((s->right == NULL) || (s->right->color == BLACK)){
				s->color = RED;
				deleteCase1(n->parent);
			}
			else{
				deleteCase4(n);
			}
		}
		else{
			deleteCase4(n);
		}
	}
	else{
		deleteCase4(n);
	}
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase4(TreeNode_t *n){
	TreeNode_t *s = sibling(n);

	if((n->parent->color == RED) &&
		(s->color == BLACK) &&
		(s->left == NULL || s->left->color == BLACK) &&
		(s->right == NULL || s->right->color == BLACK)){
		s->color = RED;
		n->parent->color = BLACK;
	}
	else{
		deleteCase5(n);
	}
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase5(TreeNode_t *n){
	TreeNode_t *s = sibling(n);

	if(s->color == BLACK){
		if((n == n->parent->left) &&
			(s->right->color == BLACK) &&
			(s->left->color == RED)){
			s->color = RED;
			s->left->color = BLACK;
			rotate_right(s);
		}
		else if((n == n->parent->right) &&
				(s->left->color == BLACK) &&
				(s->right->color == RED)){
				s->color = RED;
				s->right->color = BLACK;
				rotate_left(s);
		}
	}
	deleteCase6(n);
}


/**
Red-Black Tree Deletion Cases:
1) At the root
2) Red Sibling
3) Parent, Sibling, Left and Right children of the Sibling are all Black
4) Red Parent, Left and Right children of the Sibling are Black
5) Sibling and Sibling's outer^ child are Black, Sibling's inner^ child is Red
6) Sibling and Sibling's inner^ child are Black, Sibling's outer^ child is Red

^The inner child is defined here as the child whose value is closest to n's value

@param n the node being updated
*/
void deleteCase6(TreeNode_t *n){
	TreeNode_t *s = sibling(n);

	s->color = n->parent->color;
	n->parent->color = BLACK;

	if(n == n->parent->left){
		s->right->color = BLACK;
		rotate_left(n->parent);
	}
	else{
		s->left->color = BLACK;
		rotate_right(n->parent);
	}
}


/**
Add or Delete a node in the Red-Black Tree

@param n the value of the node to add or delete
@param loc a handle for the root node of the tree
*/
void addNode(int n, TreeNode_t **loc){
	if(*loc){
		int diff = n - (*loc)->data;
		if(diff > 0){
			if((*loc)->right){
				addNode(n,&((*loc)->right));
			}
			else{
				TreeNode_t *new = malloc(sizeof(TreeNode_t));
				*new = (TreeNode_t){.data = n, .parent = (*loc), .left = NULL, .right = NULL, .color = RED};
				(*loc)->right = new;
				insertCase1(new);
			}
		}
		else if(diff < 0){
			if((*loc)->left){
				addNode(n, &((*loc)->left));
			}
			else{
				TreeNode_t *new = malloc(sizeof(TreeNode_t));
				*new = (TreeNode_t){.data = n, .parent = (*loc), .left = NULL, .right = NULL, .color = RED};
				(*loc)->left = new;
				insertCase1(new);
			}
		}
	}
	else{
		TreeNode_t *new = malloc(sizeof(TreeNode_t));
		*new = (TreeNode_t){.data = n, .parent = NULL, .left = NULL, .right = NULL, .color = RED};
		*loc = new;
		insertCase1(*loc);
	}
}


/**
Add or Delete a node in the Red-Black Tree

@param n the value of the node to add or delete
@param loc a handle for the root node of the tree
*/
void deleteNode(int n, TreeNode_t **loc){
	if(*loc){
		int diff = n - (*loc)->data;
		if(diff > 0){
			if((*loc)->right){
				deleteNode(n, &((*loc)->right));
			}
		}
		else if(diff < 0){
			if((*loc)->left){
				deleteNode(n, &((*loc)->left));
			}	
		}
		else{
			deleteNod(*loc);
		}	
	}
}


int main(void){
	int elements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int count = 10;
	TreeNode_t *handle = NULL;
	root = &handle;
	for(int i = 0;i < count;i++){
		addNode(elements[i], root);
		printf("\nAdded: %d\n", elements[i]);
		printTree(*root, PREORDER);
	}
    printf("Preorder:\n");
    printTree(*root, PREORDER);
    printf("Inorder:\n");
    printTree(*root, INORDER);
    printf("Postorder:\n");
    printTree(*root, POSTORDER);

    for(int i = 0;i < count;i++){
        deleteNode(elements[i], root);
        printf("\nDeleted: %d\n", elements[i]);
        printTree(*root, PREORDER);
    }


	printf("Prerder:\n");
    printTree(*root, PREORDER);
    printf("Inorder:\n");
    printTree(*root, INORDER);
    printf("Postorder:\n");
    printTree(*root, POSTORDER);




	return 1;
}


