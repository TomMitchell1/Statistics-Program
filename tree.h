#ifndef TREE_H
#define TREE_H

typedef struct _node *tree;

// create a new empty BSTree
tree newTree();

// free memory associated with BSTree
tree destroyTree(tree t);

// count #nodes in a tree
int treeSize(tree t);

// insert a new value into a BSTree
tree insertNode(tree t, double v);

//Print a tree to console
void showTree(tree t);

//Find the mean of the data in the tree
double findMean(tree t);

//Find the variance of the data in the tree
double findVar(tree t);

//Find the median of a tree
double findMedian(tree t);

//Prints out the 5 number summary of the data in the tree
void fiveNumberSummary(tree t);

#endif