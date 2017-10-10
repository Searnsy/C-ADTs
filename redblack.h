#ifndef REDBLACK_H
#define REDBLACK_H

typedef enum {BLACK='b', RED='r'} color_t;

typedef enum {PREORDER, INORDER, POSTORDER} Traversal;

typedef struct TreeNode TreeNode_t;

struct TreeNode{
	int data;
	TreeNode_t *left;
	TreeNode_t *right;
	TreeNode_t *parent;
	color_t color;
};

/**
Returns the grandparent of TreeNode n (if it exists)
*/
TreeNode_t *grandparent(TreeNode_t *n);

/**
Returns the uncle of TreeNode n (if it exists)
*/
TreeNode_t *uncle(TreeNode_t *n);

/**
Returns the sibling of TreeNode n (if it exists)
*/
TreeNode_t *sibling(TreeNode_t *n);

void rotate_right(TreeNode_t *n);

void rotate_left(TreeNode_t *n);

/**
Insertion for the red-black tree is in case 1:
Root is NULL
*/
void insertCase1(TreeNode_t *n);


void insertCase2(TreeNode_t *n);


void insertCase3(TreeNode_t *n);


void insertCase4(TreeNode_t *n);


void insertCase5(TreeNode_t *n);


int numChildren(TreeNode_t *n);


TreeNode_t *findSuccessor(TreeNode_t *n);


void deleteNod(TreeNode_t *n);


void replaceNode(TreeNode_t *n, TreeNode_t *c);


void deleteOneChild(TreeNode_t *n);


void deleteCase1(TreeNode_t *n);


void deleteCase2(TreeNode_t *n);


void deleteCase3(TreeNode_t *n);


void deleteCase4(TreeNode_t *n);


void deleteCase5(TreeNode_t *n);


void deleteCase6(TreeNode_t *n);


void addNode(int n, TreeNode_t **loc);


void deleteNode(int n, TreeNode_t **loc);
#endif
