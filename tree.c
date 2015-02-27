#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "tree.h"

typedef struct _node *Link;

typedef struct _node {
	double  value;
	Link left;
	Link right;
} node;

static Link newNode(double v);
static void doShowTree(tree t, int level);
static double treeVariance(tree t,double mean);
static double treeSum(tree t);
static double findNodeValue(tree t,int nodeNum);
static double findSmallestValue(tree t);
static double findLargestValue(tree t);
static double findLowerQuartile(tree t);
static double findUpperQuartile(tree t);

// make a new node containing a value
static Link newNode(double v) {
	Link new = malloc(sizeof(node));
	assert(new != NULL);
	new->value = v;
	new->left = new->right = NULL;
	return new;
}

// create a new empty BSTree
tree newTree() {
	return NULL;
}

// free memory associated with BSTree
tree destroyTree(tree t) {
	if (t == NULL)
		/* do nothing */;
	else {
		destroyTree(t->left);
		destroyTree(t->right);
		free(t);
	}
	return NULL;
}

// count #nodes in a tree
int treeSize(tree t) {
	if (t == NULL){
		return 0;
	} else {
		return 1 + treeSize(t->left)
		         + treeSize(t->right);
	}	         
}

// insert a new value into a BSTree
tree insertNode(tree t, double v) {
	if (t == NULL)
		t = newNode(v);
	else if (v < t->value)
		t->left = insertNode(t->left, v);
	else if (v > t->value)
		t->right = insertNode(t->right, v);
	return t;
}

// display the tree sideways on the terminal
static void doShowTree(tree t, int level){
	int i;
	if (t != NULL){  
		doShowTree(t->right, level+1);
		for (i = 0; i < level; i++) printf("   ");
		// indicate leaves
		if (t->left == NULL && t->right == NULL){
			printf("!");
		}	
		printf("%.2f\n", t->value);
		doShowTree(t->left, level+1);
	}	
}

//Prints out the tree for error testing
void showTree(tree t) {
	doShowTree(t, 0);
}

//Finds the mean value for data in the tree.
double findMean(tree t){
	assert(t!=NULL);
	double sum = treeSum(t);
	int n = treeSize(t);
	double mean = sum/n;
	return mean; 
}

//Finds the total sum of all data in the tree
static double treeSum(tree t){
	if(t == NULL){
		return 0;
	} else {
		return t->value + treeSum(t->left) + treeSum(t->right);
	}	
}

//Finds the variance of the data in the tree
double findVariance(tree t){
	assert(t!=NULL);
	int n=treeSize(t);
	double mean=findMean(t);
	double var= treeVariance(t,mean)/(n-1);
	return var;
}

static double treeVariance(tree t,double mean){
	if(t == NULL){
		return 0;
	} else {
		return pow(t->value-mean,2) + treeVariance(t->left, mean) + treeVariance(t->right, mean);
	}
}

//Find the standard deviation of the data in the tree.
double findStdDeviation(tree t){
	return sqrt(findVariance(t));
}

//Find the median of the tree.
double findMedian(tree t){
	assert(t!=NULL);
	int n=treeSize(t);
	double median=0;
	if(n%2==0){
		//Number of nodes is even
		median=(findNodeValue(t,n/2) +findNodeValue(t,(n/2)+1))/2;
	} else {
		//Number of nodes is odd
		median=findNodeValue(t,(n+1)/2);
	}
	return median;
}	

//Find the value of a given node.	
static double findNodeValue(tree t,int nodeNum){
	assert(t!=NULL);
	if(treeSize(t->left)+1 == nodeNum){
		return t->value;
	} else if(treeSize(t->left)+1 > nodeNum) {
		return findNodeValue (t->left,nodeNum);
	} else {
		return findNodeValue (t->right,nodeNum-(treeSize(t->left)+1));
	}
}

//Find the lower quartile of the data in the tree.
static double findLowerQuartile(tree t){
	assert(t!=NULL);
	int n=treeSize(t);
	int median=0;
	int lowerQuartile=0;
	if(n%2 ==0){
		//N is even
		median=n/2;
		lowerQuartile= findNodeValue(t,(median+1)/2);
		
	} else {
		//N is odd
		median=(n+1)/2;
		lowerQuartile= (findNodeValue(t,median/2) +findNodeValue(t,(median/2)+1))/2;
	}
	return lowerQuartile;	
}

//Find the upper quartile of the data in the tree.
static double findUpperQuartile(tree t){
	assert(t!=NULL);
	int n=treeSize(t);
	int median=0;
	double upperQuartile=0;
	if(n%2 ==0){
		//N is even
		median=n/2;
		upperQuartile= findNodeValue(t,median+(median+1)/2);
	} else {
		//N is odd
		median=(n+1)/2;
		upperQuartile= (findNodeValue(t,median+median/2) +findNodeValue(t,median+(median/2)-1))/2;
	}
	return upperQuartile;	
}

//returns the smallest value in the tree.
static double findSmallestValue(tree t){
	assert(t!=NULL);
	return findNodeValue(t,1);
	
}

//returns the largest value in the tree.
static double findLargestValue(tree t){
	assert(t!=NULL);
	return findNodeValue(t,treeSize(t));
}

//Prints out the 5 number summary of the data in the tree.
void fiveNumberSummary(tree t){
	double quartile1 = findLowerQuartile(t);
	double quartile3 = findUpperQuartile(t);
	printf("Sample five number summary is: [");
	printf("%.2f,",findSmallestValue(t));
	printf("%.2f,",findLowerQuartile(t));
	printf("%.2f,",findMedian(t));
	printf("%.2f,",findUpperQuartile(t));
	printf("%.2f]\n",findLargestValue(t));
	printf("Sample interquartile range: %.2f\n",quartile3-quartile1);

}

//Prints out a 95% and 99% confidence interval for the data tree
//This assumes that the number of data points imported into
//the program is above 40, otherwise it will not be as accurate
void confidenceInterval(tree t){
	int n= treeSize(t);
	double mean=findMean(t);
	double stdDeviation=findStdDeviation(t);
	double lowerLimit= mean-Z_SCORE_95_PERCENT*(stdDeviation/sqrt(n));
	double upperLimit= mean+Z_SCORE_95_PERCENT*(stdDeviation/sqrt(n));
	printf("95%% confidence interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
	
	lowerLimit= mean-Z_SCORE_99_PERCENT*(stdDeviation/sqrt(n));
	upperLimit= mean+Z_SCORE_99_PERCENT*(stdDeviation/sqrt(n));
	printf("99%% confidence interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
}

//Prints out a 95% and 99% prediction interval for further 
//data values. This does not need for the data to have at least 
//40 data values to be accurate, however it is most accurate for large 
//sets of data
void predictionInterval(tree t){
	int n= treeSize(t);
	double mean=findMean(t);
	double stdDeviation=findStdDeviation(t);
	
	double lowerLimit=0;
	double upperLimit=0;
	
	double tScore=0;
	
	if(n>250){
		tScore=T_SCORE_INFINITE_95_PERCENT;
	} else {
		tScore=T_SCORE_250_95_PERCENT;	
	}
	lowerLimit= mean-tScore* (stdDeviation*sqrt(1+1/n));
	upperLimit= mean+tScore*(stdDeviation*sqrt(1+1/n));	
	printf("95%% prediction interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
	
	if(n>250){
		tScore=T_SCORE_INFINITE_99_PERCENT;
	} else {
		tScore=T_SCORE_250_99_PERCENT;	
	}
		
	lowerLimit= mean-tScore*(stdDeviation*sqrt(1+1/n));
	upperLimit= mean+tScore*(stdDeviation*sqrt(1+1/n));	
	printf("99%% prediction interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
}