#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "tree.h"


void treeTests(void);

int main( int argc, char* argv[]) {

	treeTests();

	return EXIT_SUCCESS;
}

void treeTests(void){
	//Test tree construction
	tree t=newTree();
	//Test adding to the tree
	t=insertNode(t,5);
	assert(t!=NULL);
	assert(treeSize(t)==1);
	t=insertNode(t,7);
	assert(treeSize(t)==2);
	t=insertNode(t,3);
	assert(treeSize(t)==3);
	t=insertNode(t,6);
	assert(treeSize(t)==4);
	t=insertNode(t,1);
	assert(treeSize(t)==5);
	t=insertNode(t,10);
	assert(treeSize(t)==6);
	t=insertNode(t,8);
	assert(treeSize(t)==7);
	showTree(t);
	
	assert(round(findMean(t) * 100) / 100==5.71);
	//assert(findMedian(t)==5.5);
	if(t!=NULL){
		
		//Print out the statistical information
		printf("Number of data points is %d\n",treeSize(t));
		printf("Sample mean = %.2f\n",findMean(t));
		printf("Sample variance = %.2f\n",findVariance(t));
		printf("Sample standard deviation = %.2f\n",findStdDeviation(t));
		printf("Sample median = %.2f\n",findMedian(t));
		fiveNumberSummary(t);
		confidenceInterval(t);
		predictionInterval(t);
		
		
		
		
		
	}
	printf("\n\n\n");
	t=insertNode(t,8);
	assert(treeSize(t)==8);
	t=insertNode(t,2);
	assert(treeSize(t)==9);
	t=insertNode(t,11);
	assert(treeSize(t)==10);
	t=insertNode(t,7);
	assert(treeSize(t)==11);
	t=insertNode(t,7);
	assert(treeSize(t)==12);
	t=insertNode(t,8);
	assert(treeSize(t)==13);
	t=insertNode(t,4);
	assert(treeSize(t)==14);
	t=insertNode(t,6);
	assert(treeSize(t)==15);
	assert(t!=NULL);
	assert(treeSize(t)==15);
	showTree(t);
	
	//assert(findMean(t)==5.25);
	//assert(findMedian(t)==5.5);
	if(t!=NULL){
		
		//Print out the statistical information
		printf("Number of data points is %d\n",treeSize(t));
		printf("Sample mean = %.2f\n",findMean(t));
		printf("Sample variance = %.2f\n",findVariance(t));
		printf("Sample standard deviation = %.2f\n",findStdDeviation(t));
		printf("Sample median = %.2f\n",findMedian(t));
		fiveNumberSummary(t);
		confidenceInterval(t);
		predictionInterval(t);
		
		
		
		
		
	}
	
	
	
	//Test freeing memory that the tree uses
	t=destroyTree(t);
	assert(treeSize(t)==0);
	assert(t==NULL);
}