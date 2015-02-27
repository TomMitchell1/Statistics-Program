#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
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

// display a BSTree (sideways)
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

void showTree(tree t) {
	doShowTree(t, 0);
}

double findMean(tree t){
	assert(t!=NULL);
	double sum = treeSum(t);
	int n = treeSize(t);
	double mean = sum/n;
	return mean; 
}

static double treeSum(tree t){
	if(t == NULL){
		return 0;
	} else {
		return t->value + treeSum(t->left) + treeSum(t->right);
	}	
}

double findVar(tree t){
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
		return (t->value-mean)*(t->value-mean) + treeVariance(t->left, mean) + treeVariance(t->right, mean);
	}
}

//Find the median of the tree
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

//Find the value of a given node	
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

//Find the lower quartile of the data in the tree
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

//Find the upper quartile of the data in the tree
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

//returns the smallest value in the tree
static double findSmallestValue(tree t){
	assert(t!=NULL);
	return findNodeValue(t,1);
	
}

//returns the largest value in the tree
static double findLargestValue(tree t){
	assert(t!=NULL);
	return findNodeValue(t,treeSize(t));
}

//Prints out the 5 number summary of the data in the tree
void fiveNumberSummary(tree t){
	printf("Five number summary is: [");
	printf("%.2f,",findSmallestValue(t));
	printf("%.2f,",findLowerQuartile(t));
	printf("%.2f,",findMedian(t));
	printf("%.2f,",findUpperQuartile(t));
	printf("%.2f]\n",findLargestValue(t));


}