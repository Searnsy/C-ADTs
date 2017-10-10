/**
This program implements a Binary Search Tree ADT. The goal is to practice
ADT development in c.

@author Andrew Searns <ab2157@rit.edu>
*/

#ifndef _BSTADT_H_
#define _BSTADT_H_

#ifndef _BST_IMPL_
typedef struct {} BstADT;
#endif

typedef STYPE tdata_t;
typedef enum {PREORDER, INORDER, POSTORDER} Traversal;

BstADT* tree_create(void);
void tree_destroy(BstADT* tree);

void tree_add(BstADT* tree, tdata_t* n);
int tree_contains(BstADT* tree, tdata_t* n);
void tree_remove(BstADT* tree, tdata_t* n);

void print_tree(BstADT* tree, Traversal trav);

#endif
