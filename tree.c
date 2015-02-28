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
static double determineTScore95(int n);
static double determineTScore99(int n);
static bool twoSidedHypothesisTest (tree t,double hypothesis);
static bool oneSidedHypothesisTest (tree t,char c, double hypothesis);
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
	else if (v <= t->value)
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
	double lowerLimit= mean-Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	double upperLimit= mean+Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	printf("95%% confidence interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
	
	lowerLimit= mean-Z_SCORE_99_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	upperLimit= mean+Z_SCORE_99_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
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
	
	double tScore=determineTScore95(n-1); //n-1 as 1 less degrees of freedom
	
	
	lowerLimit= mean-tScore* (stdDeviation*sqrt(1+1/n));
	upperLimit= mean+tScore*(stdDeviation*sqrt(1+1/n));	
	printf("95%% prediction interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
	
	tScore=determineTScore99(n-1); //n-1 as 1 less degrees of freedom
		
	lowerLimit= mean-tScore*(stdDeviation*sqrt(1+1/n));
	upperLimit= mean+tScore*(stdDeviation*sqrt(1+1/n));	
	printf("99%% prediction interval for the sample is: ");
	printf("[%.2f,%.2f]\n",lowerLimit,upperLimit);
}

//Given the number of data points this function will return the correct t value 
//for a 95% confidence interval
static double determineTScore95(int n){
	double score=0;
	if(n==1){
		score=T_SCORE_1_95_PERCENT;
	} else if(n==2){
		score=T_SCORE_2_95_PERCENT;
	} else if(n==3){
		score=T_SCORE_3_95_PERCENT;
	} else if(n==4){
		score=T_SCORE_4_95_PERCENT;
	} else if(n==5){
		score=T_SCORE_5_95_PERCENT;
	} else if(n==6){	
		score=T_SCORE_6_95_PERCENT;
	} else if(n==7){
		score=T_SCORE_7_95_PERCENT;
	} else if(n==8){
		score=T_SCORE_8_95_PERCENT;
	} else if(n==9){
		score=T_SCORE_9_95_PERCENT;
	} else if(n==10){
		score=T_SCORE_10_95_PERCENT;		
	} else if(n==11){
		score=T_SCORE_11_95_PERCENT;
	} else if(n==12){
		score=T_SCORE_12_95_PERCENT;
	} else if(n==13){
		score=T_SCORE_13_95_PERCENT;
	} else if(n==14){
		score=T_SCORE_14_95_PERCENT;
	} else if(n==15){
		score=T_SCORE_15_95_PERCENT;
	} else if(n==16){
		score=T_SCORE_16_95_PERCENT;
	} else if(n==17){
		score=T_SCORE_17_95_PERCENT;	
	} else if(n==18){
		score=T_SCORE_18_95_PERCENT;
	} else if(n==19){
		score=T_SCORE_19_95_PERCENT;
	} else if(n==20){
		score=T_SCORE_20_95_PERCENT;
	} else if(n==21){
		score=T_SCORE_21_95_PERCENT;
	} else if(n==22){
		score=T_SCORE_22_95_PERCENT;
	} else if(n==23){
		score=T_SCORE_23_95_PERCENT;
	} else if(n==24){
		score=T_SCORE_24_95_PERCENT;
	} else if(n==25){
		score=T_SCORE_25_95_PERCENT;
	} else if(n==26){
		score=T_SCORE_26_95_PERCENT;
	} else if(n==27){
		score=T_SCORE_27_95_PERCENT;
	} else if(n==28){
		score=T_SCORE_28_95_PERCENT;
	} else if(n==29){
		score=T_SCORE_29_95_PERCENT;
	} else if(n==30){
		score=T_SCORE_30_95_PERCENT;
	} else if(n==31){
		score=T_SCORE_31_95_PERCENT;
	} else if(n==32){
		score=T_SCORE_32_95_PERCENT;
	} else if(n==33){
		score=T_SCORE_33_95_PERCENT;
	} else if(n==34){
		score=T_SCORE_34_95_PERCENT;
	} else if(n==35){
		score=T_SCORE_35_95_PERCENT;
	} else if(n==36){
		score=T_SCORE_36_95_PERCENT;
	} else if(n==37){
		score=T_SCORE_37_95_PERCENT;
	} else if(n==38){
		score=T_SCORE_38_95_PERCENT;
	} else if(n==39){
		score=T_SCORE_39_95_PERCENT;
	} else if(n==40){
		score=T_SCORE_40_95_PERCENT;
	} else if(n<=60){
		score=T_SCORE_60_95_PERCENT;
	} else if(n<=80){
		score=T_SCORE_80_95_PERCENT;
	} else if(n<=100){
		score=T_SCORE_100_95_PERCENT;
	} else if(n<=120){
		score=T_SCORE_120_95_PERCENT;
	} else if(n<=140){
		score=T_SCORE_140_95_PERCENT;
	} else if(n<=160){
		score=T_SCORE_160_95_PERCENT;
	} else if(n<=180){
		score=T_SCORE_180_95_PERCENT;
	} else if(n<=200){
		score=T_SCORE_200_95_PERCENT;
	} else if(n<=250){
		score=T_SCORE_250_95_PERCENT;
	} else {
		score=T_SCORE_INFINITE_95_PERCENT;
	}
	return score;
}

//Given the number of data points this function will return the correct t value 
//for a 99% confidence interval
static double determineTScore99(int n){
	double score=0;
	if(n==1){
		score=T_SCORE_1_99_PERCENT;
	} else if(n==2){
		score=T_SCORE_2_99_PERCENT;
	} else if(n==3){
		score=T_SCORE_3_99_PERCENT;
	} else if(n==4){
		score=T_SCORE_4_99_PERCENT;
	} else if(n==5){
		score=T_SCORE_5_99_PERCENT;
	} else if(n==6){	
		score=T_SCORE_6_99_PERCENT;
	} else if(n==7){
		score=T_SCORE_7_99_PERCENT;
	} else if(n==8){
		score=T_SCORE_8_99_PERCENT;
	} else if(n==9){
		score=T_SCORE_9_99_PERCENT;
	} else if(n==10){
		score=T_SCORE_10_99_PERCENT;		
	} else if(n==11){
		score=T_SCORE_11_99_PERCENT;
	} else if(n==12){
		score=T_SCORE_12_99_PERCENT;
	} else if(n==13){
		score=T_SCORE_13_99_PERCENT;
	} else if(n==14){
		score=T_SCORE_14_99_PERCENT;
	} else if(n==15){
		score=T_SCORE_15_99_PERCENT;
	} else if(n==16){
		score=T_SCORE_16_99_PERCENT;
	} else if(n==17){
		score=T_SCORE_17_99_PERCENT;	
	} else if(n==18){
		score=T_SCORE_18_99_PERCENT;
	} else if(n==19){
		score=T_SCORE_19_99_PERCENT;
	} else if(n==20){
		score=T_SCORE_20_99_PERCENT;
	} else if(n==21){
		score=T_SCORE_21_99_PERCENT;
	} else if(n==22){
		score=T_SCORE_22_99_PERCENT;
	} else if(n==23){
		score=T_SCORE_23_99_PERCENT;
	} else if(n==24){
		score=T_SCORE_24_99_PERCENT;
	} else if(n==25){
		score=T_SCORE_25_99_PERCENT;
	} else if(n==26){
		score=T_SCORE_26_99_PERCENT;
	} else if(n==27){
		score=T_SCORE_27_99_PERCENT;
	} else if(n==28){
		score=T_SCORE_28_99_PERCENT;
	} else if(n==29){
		score=T_SCORE_29_99_PERCENT;
	} else if(n==30){
		score=T_SCORE_30_99_PERCENT;
	} else if(n==31){
		score=T_SCORE_31_99_PERCENT;
	} else if(n==32){
		score=T_SCORE_32_99_PERCENT;
	} else if(n==33){
		score=T_SCORE_33_99_PERCENT;
	} else if(n==34){
		score=T_SCORE_34_99_PERCENT;
	} else if(n==35){
		score=T_SCORE_35_99_PERCENT;
	} else if(n==36){
		score=T_SCORE_36_99_PERCENT;
	} else if(n==37){
		score=T_SCORE_37_99_PERCENT;
	} else if(n==38){
		score=T_SCORE_38_99_PERCENT;
	} else if(n==39){
		score=T_SCORE_39_99_PERCENT;
	} else if(n==40){
		score=T_SCORE_40_99_PERCENT;
	} else if(n<=60){
		score=T_SCORE_60_99_PERCENT;
	} else if(n<=80){
		score=T_SCORE_80_99_PERCENT;
	} else if(n<=100){
		score=T_SCORE_100_99_PERCENT;
	} else if(n<=120){
		score=T_SCORE_120_99_PERCENT;
	} else if(n<=140){
		score=T_SCORE_140_99_PERCENT;
	} else if(n<=160){
		score=T_SCORE_160_99_PERCENT;
	} else if(n<=180){
		score=T_SCORE_180_99_PERCENT;
	} else if(n<=200){
		score=T_SCORE_200_99_PERCENT;
	} else if(n<=250){
		score=T_SCORE_250_99_PERCENT;
	} else {
		score=T_SCORE_INFINITE_99_PERCENT;
	}
	return score;
}

//Given a tree and a type of hypothesis test, this function with return a 
//boolean saying whether or not to reject the null hypothesis
bool hypothesisTesting(tree t,char c,double hypothesis){
	bool reject=FALSE;
	
	if(c=='a'){
		//Then the test to use is a two sided alternative
		reject=twoSidedHypothesisTest (t,hypothesis);
	} else {
		reject=oneSidedHypothesisTest (t,c,hypothesis);
	}
	return reject;
}

static bool twoSidedHypothesisTest (tree t,double hypothesis){
	bool reject=FALSE;
	int n=treeSize(t);
	double mean=findMean(t);
	double stdDeviation=sqrt(findVariance(t));
	double lowerLimit= hypothesis-Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	double upperLimit= hypothesis+Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	if(mean <lowerLimit || mean > upperLimit){
		reject =TRUE;
	}
	return reject;
}

static bool oneSidedHypothesisTest (tree t,char c, double hypothesis){
	bool reject=FALSE;
	int n=treeSize(t);
	double mean=findMean(t);
	double stdDeviation=sqrt(findVariance(t));
	double lowerLimit= hypothesis-Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	double upperLimit= hypothesis+Z_SCORE_95_PERCENT_2_SIDED*(stdDeviation/sqrt(n));
	if(c == 'b'){
		if(mean >upperLimit){
			reject =TRUE;
		}
	} else {
		//char is c	
		if(mean <lowerLimit){
			reject =TRUE;
		}
	}	
	return reject;
}
