/*
	Statistics Package by Tom Mitchell

	This program takes uses a file location from the command line 
	when the program is run. This file has to have 1 piece of data
	per each line of the file.
	
	When the data is fully imported the program then prints out 
	statistical data.
	This includes:
		-Mean
		-Variance
		-Standard deviation
		-5 number summary
		-Confidence intervals 99% and 95%
		-Prediction intervals 99% and 95%
	
	The user will then be able to test hypotheses to see if claims
	about the mean of the data should be rejected or accepted.
	
	Tests for mean,variance and standard deviation were done in test function.
	The tests for the 5 number summary and confidence intervals were done by
	checking the results against the results from matlab.
	
	For confidence intervals and hypothesis testing are based off calculations
	on the mean on an arbitrary distribution where it is not known if the sample
	came from a normally distribution population. This can be approximated by a 
	normal distribution if the number of data points is large enough n>40.
		
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "tree.h"

#define CORRECT_NUMBER_OF_ARGS 2
#define FILE_ARGUEMENT 1
#define MAX_STRING_SIZE 3
#define STRINGS_EQUAL 0

tree importData(char* string);
void treeTests(void);
void stats(tree t);

int main( int argc, char* argv[]) {
	tree t;
	//treeTests();
	if ( argc == CORRECT_NUMBER_OF_ARGS ){
		t=importData(argv[FILE_ARGUEMENT]);
		stats(t);
	} else {
		printf("Did not give a file name.\n");
	}
	
	
	return EXIT_SUCCESS;
}

void treeTests(void){
	char string[3];
	double hypothesis=0;
	char hypothesisTestType='0';
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
	
	assert(t!=NULL);
	assert(round(findMean(t) * 100) / 100==5.71);
	assert(findMedian(t)==6);
	assert(round(findVariance(t) * 100) / 100==9.24);
	assert(round(findStdDeviation(t) * 100) / 100==3.04);
	
	//Print out the statistical information
	printf("Number of data points is %d\n",treeSize(t));
	printf("Sample mean = %.2f\n",findMean(t));
	printf("Sample variance = %.2f\n",findVariance(t));
	printf("Sample standard deviation = %.2f\n",findStdDeviation(t));
	printf("Sample median = %.2f\n",findMedian(t));
	fiveNumberSummary(t);
	confidenceInterval(t);
	predictionInterval(t);	
	
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
	
	assert(t!=NULL);
	assert(round(findMean(t) * 100) / 100==6.2);
	assert(findMedian(t)==7);
	assert(round(findVariance(t) * 100) / 100==7.89);
	assert(round(findStdDeviation(t) * 100) / 100==2.81);
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
		printf("Would you like to test hypotheses?\n");
		printf("yes or no: "); 
		scanf("%s",string);
		while(strcmp (string,"yes") == 0){
		
			printf("Please enter a claimed average for hypothesis testing:");
			scanf("%lf",&hypothesis);
			printf("\nWhat sort of hypothesis test would you like to use?\n");
			printf("Please type a,b,c for the type of hypothesis test:\n\n");
			printf("  a)  Two-sided alternative test\n");
			printf("  b)  One-sided alternative test: ");
			printf("sample mean is not greater than hypothesis\n");
			printf("  c)  One-sided alternative test: ");
			printf("sample mean is not less than hypothesis\n\n");
		
			printf("Hypothesis test: ");
			scanf(" %c",&hypothesisTestType);
		
			printf("\n");
		
			if(hypothesisTesting(t,hypothesisTestType,hypothesis)==TRUE){
				printf("The hypothesis should be rejected\n");
				printf(" at a significance level of 0.05.\n");
				if(hypothesisTestType=='a'){
					printf("Using a two-sided alternative test.\n");
				} else {
					printf("Using a one-sided alternative test.\n");
				}
			} else {
				printf("The hypothesis should not be rejected");
				printf(" at a significance level of 0.05.\n");
				if(hypothesisTestType=='a'){
					printf("Using a two-sided alternative test.\n");
				} else {
					printf("Using a one-sided alternative test.\n");
				}
			}
			printf("\nWould you like to test hypotheses?\n");
			printf("type yes or no: "); 
			scanf("%s",string);
		}	
	}
	
	
	
	//Test freeing memory that the tree uses
	t=destroyTree(t);
	assert(treeSize(t)==0);
	assert(t==NULL);
}

tree importData(char* string){
	tree t=newTree();
	double data;
	FILE *fp;
	fp = fopen(string, "r+");
	if(fp==NULL){
	} else {
		while(fscanf(fp,"%lf",&data) == 1)  {  
        	t=insertNode(t,data);  
		}  
	}
	return t;
}

void stats(tree t){
	char string[MAX_STRING_SIZE];
	double hypothesis=0;
	char hypothesisTestType='0';
	if(t!=NULL){
		//Print out the statistical information
		printf("Number of data points is %d\n",treeSize(t));
		printf("Sample mean = %.2f\n",findMean(t));
		printf("Sample variance = %.2f\n",findVariance(t));
		printf("Sample standard deviation = %.2f\n",findStdDeviation(t));
		fiveNumberSummary(t);
		confidenceInterval(t);
		predictionInterval(t);
		printf("Would you like to test hypotheses?\n");
		printf("yes or no: "); 
		scanf("%s",string);
		while(strcmp (string,"yes") == STRINGS_EQUAL){
		
			printf("Please enter a claimed average for hypothesis testing:");
			scanf("%lf",&hypothesis);
			printf("\nWhat sort of hypothesis test would you like to use?\n");
			printf("Please type a,b,c for the type of hypothesis test:\n\n");
			printf("  a)  Two-sided alternative test\n");
			printf("  b)  One-sided alternative test: ");
			printf("sample mean is not greater than hypothesis\n");
			printf("  c)  One-sided alternative test: ");
			printf("sample mean is not less than hypothesis\n\n");
		
			printf("Hypothesis test: ");
			scanf(" %c",&hypothesisTestType);
		
			printf("\n");
		
			if(hypothesisTesting(t,hypothesisTestType,hypothesis)==TRUE){
				printf("The hypothesis should be rejected\n");
				printf(" at a significance level of 0.05.\n");
				if(hypothesisTestType=='a'){
					printf("Using a two-sided alternative test.\n");
				} else {
					printf("Using a one-sided alternative test.\n");
				}
			} else {
				printf("The hypothesis should not be rejected");
				printf(" at a significance level of 0.05.\n");
				if(hypothesisTestType=='a'){
					printf("Using a two-sided alternative test.\n");
				} else {
					printf("Using a one-sided alternative test.\n");
				}
			}
			printf("\nWould you like to test hypotheses?\n");
			printf("type yes or no: "); 
			scanf("%s",string);
		}	
	}
}