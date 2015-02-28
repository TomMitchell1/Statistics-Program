#ifndef TREE_H
#define TREE_H

typedef struct _node *tree;

typedef int bool;
#define TRUE 1
#define FALSE 0


//For 2 sided confidence intervals
#define Z_SCORE_95_PERCENT_2_SIDED 1.96
#define Z_SCORE_99_PERCENT_2_SIDED 2.575

#define Z_SCORE_95_PERCENT_1_SIDED 1.645
#define Z_SCORE_99_PERCENT_1_SIDED 2.33

//Used for 95% prediction interval with t distribution
#define T_SCORE_1_95_PERCENT 6.314
#define T_SCORE_2_95_PERCENT 2.920
#define T_SCORE_3_95_PERCENT 2.353
#define T_SCORE_4_95_PERCENT 2.132
#define T_SCORE_5_95_PERCENT 2.015
#define T_SCORE_6_95_PERCENT 1.943
#define T_SCORE_7_95_PERCENT 1.895
#define T_SCORE_8_95_PERCENT 1.860
#define T_SCORE_9_95_PERCENT 1.833
#define T_SCORE_10_95_PERCENT 1.812
#define T_SCORE_11_95_PERCENT 1.796
#define T_SCORE_12_95_PERCENT 1.782
#define T_SCORE_13_95_PERCENT 1.771
#define T_SCORE_14_95_PERCENT 1.761
#define T_SCORE_15_95_PERCENT 1.753
#define T_SCORE_16_95_PERCENT 1.746
#define T_SCORE_17_95_PERCENT 1.740
#define T_SCORE_18_95_PERCENT 1.734
#define T_SCORE_19_95_PERCENT 1.729
#define T_SCORE_20_95_PERCENT 1.725
#define T_SCORE_21_95_PERCENT 1.721
#define T_SCORE_22_95_PERCENT 1.717
#define T_SCORE_23_95_PERCENT 1.714
#define T_SCORE_24_95_PERCENT 1.711
#define T_SCORE_25_95_PERCENT 1.708
#define T_SCORE_26_95_PERCENT 1.706
#define T_SCORE_27_95_PERCENT 1.703
#define T_SCORE_28_95_PERCENT 1.701
#define T_SCORE_29_95_PERCENT 1.699
#define T_SCORE_30_95_PERCENT 1.697
#define T_SCORE_31_95_PERCENT 1.696
#define T_SCORE_32_95_PERCENT 1.694
#define T_SCORE_33_95_PERCENT 1.692
#define T_SCORE_34_95_PERCENT 1.691
#define T_SCORE_35_95_PERCENT 1.690
#define T_SCORE_36_95_PERCENT 1.688
#define T_SCORE_37_95_PERCENT 1.687
#define T_SCORE_38_95_PERCENT 1.686
#define T_SCORE_39_95_PERCENT 1.685
#define T_SCORE_40_95_PERCENT 1.684
#define T_SCORE_60_95_PERCENT 1.671
#define T_SCORE_80_95_PERCENT 1.664
#define T_SCORE_100_95_PERCENT 1.660
#define T_SCORE_120_95_PERCENT 1.658
#define T_SCORE_140_95_PERCENT 1.656
#define T_SCORE_160_95_PERCENT 1.654
#define T_SCORE_180_95_PERCENT 1.653
#define T_SCORE_200_95_PERCENT 1.653
#define T_SCORE_250_95_PERCENT 1.651
#define T_SCORE_INFINITE_95_PERCENT 1.645

//Used for 99% prediction interval with t distribution
#define T_SCORE_1_99_PERCENT 31.82
#define T_SCORE_2_99_PERCENT 6.965
#define T_SCORE_3_99_PERCENT 4.541
#define T_SCORE_4_99_PERCENT 3.747
#define T_SCORE_5_99_PERCENT 3.365
#define T_SCORE_6_99_PERCENT 3.143
#define T_SCORE_7_99_PERCENT 2.998
#define T_SCORE_8_99_PERCENT 2.896
#define T_SCORE_9_99_PERCENT 2.821
#define T_SCORE_10_99_PERCENT 2.764
#define T_SCORE_11_99_PERCENT 2.718
#define T_SCORE_12_99_PERCENT 2.681
#define T_SCORE_13_99_PERCENT 2.650
#define T_SCORE_14_99_PERCENT 2.624
#define T_SCORE_15_99_PERCENT 2.602
#define T_SCORE_16_99_PERCENT 2.583
#define T_SCORE_17_99_PERCENT 2.567
#define T_SCORE_18_99_PERCENT 2.552
#define T_SCORE_19_99_PERCENT 2.539
#define T_SCORE_20_99_PERCENT 2.528
#define T_SCORE_21_99_PERCENT 2.518
#define T_SCORE_22_99_PERCENT 2.508
#define T_SCORE_23_99_PERCENT 2.500
#define T_SCORE_24_99_PERCENT 2.492
#define T_SCORE_25_99_PERCENT 2.485
#define T_SCORE_26_99_PERCENT 2.479
#define T_SCORE_27_99_PERCENT 2.473
#define T_SCORE_28_99_PERCENT 2.467
#define T_SCORE_29_99_PERCENT 2.462
#define T_SCORE_30_99_PERCENT 2.457
#define T_SCORE_31_99_PERCENT 2.453
#define T_SCORE_32_99_PERCENT 2.449
#define T_SCORE_33_99_PERCENT 2.445
#define T_SCORE_34_99_PERCENT 2.441
#define T_SCORE_35_99_PERCENT 2.438
#define T_SCORE_36_99_PERCENT 2.434
#define T_SCORE_37_99_PERCENT 2.431
#define T_SCORE_38_99_PERCENT 2.429
#define T_SCORE_39_99_PERCENT 2.426
#define T_SCORE_40_99_PERCENT 2.423
#define T_SCORE_60_99_PERCENT 2.390
#define T_SCORE_80_99_PERCENT 2.374
#define T_SCORE_100_99_PERCENT 2.364
#define T_SCORE_120_99_PERCENT 2.358
#define T_SCORE_140_99_PERCENT 2.353
#define T_SCORE_160_99_PERCENT 2.350
#define T_SCORE_180_99_PERCENT 2.347
#define T_SCORE_200_99_PERCENT 2.345
#define T_SCORE_250_99_PERCENT 2.341
#define T_SCORE_INFINITE_99_PERCENT 2.326


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

//Given a tree and a type of hypothesis test, this function with return a 
//boolean saying whether or not to reject the null hypothesis
bool hypothesisTesting(tree t,char c,double hypothesis);
#endif