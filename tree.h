#ifndef TREE_H
#define TREE_H

typedef struct _node *tree;

#define Z_SCORE_95_PERCENT 1.96
#define Z_SCORE_99_PERCENT 2.575
#define T_SCORE_INFINITE_99_PERCENT 2.326
#define T_SCORE_250_99_PERCENT 2.341
#define T_SCORE_INFINITE_95_PERCENT 1.645
#define T_SCORE_250_95_PERCENT 1.651


// create a new empty BSTree
tree newTree();

// free memory associated with BSTree
tree destroyTree(tree t);

// count #nodes in a tree
int treeSize(tree t);

// insert a new value into a BSTree
tree insertNode(tree t, double v);

//Prints out the tree for error testing
//Prints it sideways to the terminal
void showTree(tree t);

//Find the mean of the data in the tree
double findMean(tree t);

//Find the variance of the data in the tree
double findVariance(tree t);

//Find the standard deviation of the data in the tree
double findStdDeviation(tree t);

//Find the median of a tree
double findMedian(tree t);

//Prints out the 5 number summary of the data in the tree
void fiveNumberSummary(tree t);

//Prints out a 95% and 99% confidence interval for the data tree
//This assumes that the number of data points imported into
//the program is above 40.
void confidenceInterval(tree t);

//Prints out a 95% and 99% prediction interval for further 
//data values. This does not need for the data to have at least 
//40 data values to be accurate, however it is most accurate for large 
//sets of data
void predictionInterval(tree t);

#endif