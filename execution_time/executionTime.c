#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

#include "treeChar.h"

#define DELTA 100
#define K 0.05 //max error
#define ZA 1.96 //Z * (1 - alpha/2) alpha = 0.05

#define TARA 0
#define LORDO 1


/*
	
	minimum measurable time from the Clock system
	@return Granularity
*/
int granularita(); 


/*
	@param repetitionMisure: number of tempoMedioNetto repetitions
	@param dataLength: length of the string
	@param tMi:n minimum measurement time
	@return 
*/
void misurazione (int repetitionMisure,int dataLength,int tMin);


/*
	@param dataLength: length of the string
	@param tMin: minimum measurement time
	@return avarage execution time
*/
int tempoMedioNetto(int dataLength,int tMin);


/*
	@param dataLength: length of the string
	@param tMin: minimum measurement time
	@param execteProgram: it allows to switch from ripTara to ripLordo
	@return event repetition numbers by dichotomy
*/
int calcolaRip(int dataLength,int tMin,int executeProgram);

/*
	@param dataLength: length of the string
	@return random alphabetic string
*/
char *prepara(int dataLength);

/*
	@return pseudoRandom number
*/
double randomAlg8(double *seed);


/*
	@param string a, VALID Char a-z
	@return |V|,|E|,leaves graph dot format
*/

int Algoritmo(int argc, char *argv);



/*
	save in "Execution Time.txt" the algorithm times for the different string lengths
*/
int main(){
	

	int repetition = 10;
	int dataLength = 4500;
	int tMin = granularita() / K;
	printf("tMin: %d\n",tMin);
	misurazione(repetition,dataLength,tMin);
	return 0;
}

//based on Algorithm 4
int granularita(){
	clock_t t0,t1;
	t0 = clock();
	t1 = clock();
	while ( t0 == t1){
		t1 = clock();
	}
	return t1-t0;
}

//based on Algorithm 9 
void misurazione (int repetitionMeasure,int dataLength,int tMin){

	int totalTime = 0;
	int sum2 = 0;
	int cn = 0; //cardinality of the sample

	double delta;
	double s;
	double measure;
	int m;
	do {
		for(int i = 0; i < repetitionMeasure; i++) {
			m = tempoMedioNetto(dataLength,tMin);
			totalTime += m;
			sum2 += pow(m,2);
		}
		cn += repetitionMeasure;
		measure = totalTime/cn;
		s = sqrt(sum2/cn - (measure*measure));
		delta = (1/sqrt(cn)) * ZA * s;
	} while(delta > DELTA);
	printf("Lunghezza dato: %d, Delta: %d, K: %f, ZA: %f\n",dataLength,DELTA,K,ZA);
	printf("Tempio medio: %f, delta: %f\n",measure/CLOCKS_PER_SEC,delta/CLOCKS_PER_SEC);
	return;
}

//based on Algorithm 7
int tempoMedioNetto(int dataLength,int tMin){
	int ripTara = calcolaRip(dataLength,tMin,TARA);
	int ripLordo = calcolaRip(dataLength,tMin,LORDO);

	char *string;
	clock_t t0 = clock();

	for(int i = 0; i < ripTara; i++) {
		string = prepara(dataLength);
	}

	clock_t t1 = clock();
	clock_t tTara = t1 - t0;	//total execution time Tara

	for(int i = 0; i < ripLordo; i++) {
    	string = prepara(dataLength);
    	Algoritmo(2,string);
  	}

  	t1 = clock();
  	int tLordo = t1 - t0;	//total execution time Lordo
  	int tMedio = (tLordo/ripLordo) - (tTara/ripTara);	//avarage time execution

  	return tMedio;
}

//based on Algorithm 5
int calcolaRip(int dataLength,int tMin,int executeProgram){
	char *string;
	clock_t t0,t1 = 0;
	int rip = 1;

	while(( t1 - t0 ) <= tMin ){
		rip *= 2;
		t0 = clock();
		for(int i = 0; i <= rip; i++){
			string = prepara(dataLength);
			if(executeProgram){ //Only in ripLordo
				Algoritmo(2,string);
			}
		}
		t1 = clock();
	}
	int max = rip;
	int min = rip/2;
	int cicliErrati = 5;

	while( (max - min) >= cicliErrati ) {
		rip = (max + min)/2;
		t0 = clock();
		for(int i = 0; i <= rip; i++){
			string = prepara(dataLength);
			if(executeProgram){ //Only in ripLordo
				Algoritmo(2,string);
			}
		}
		t1 = clock();
		if( (t1 - t0) <= tMin){
			min = rip;
		} else {
			max = rip;
		}
	}
	return max;
}

char *prepara(int dataLength) {
	char *string = malloc(dataLength + 1);
	double seed = clock();
	for(int i = 0; i < dataLength; i++) {
		string[i] = 97 + (int) round(randomAlg8(&seed)*25); //round: nearest integer value
	}
	string[dataLength] = 0;
	return string;
}

//based on Algorithm 8
double randomAlg8(double *seed){ 
	
  const int a = 16087;
  const int m = 2147483647;
  const int q = 127773;
  const int r = 2836;

  double lo, hi, test;

  hi = trunc(*seed / q);
  lo = *seed - q * hi;
  test = a * lo - r * hi;
  if (test < 0.0) {
    *seed = test + m;
  } else {
    *seed = test;
  }
  return *seed / m;
}


int Algoritmo(int argc, char *argv){
	//initialization
	int lenString = 0;
	int leaves = 0;
	if(argc > 1){
		lenString = strlen(argv);
		leaves = 1;
	}
	int strNumChar[26] = {0}; //each location is the number of character repetitions 0 = a , 25 = z
	int value;
	struct charNode *treeChar = NULL;	
	


	//creation tree
	for(int i = 0; i < lenString; i++){
		treeChar = treeCharInsert(treeChar,argv[i],0,&leaves);
		value = ((int) argv[i])-97;
		strNumChar[value] ++;
	}


	//searching the maximum/minimum number of repetitions of a character
	int maxCharacterRepetitions = 0;	//char repeat more time
	for(int i = 0; i < 26; i++){
		if(maxCharacterRepetitions < strNumChar[i]){
			maxCharacterRepetitions = strNumChar[i];
		}
	}

	int minCharacterRepetitions = maxCharacterRepetitions;	//char repeat less time
	for(int i = 0; i < 26; i++){
		if(minCharacterRepetitions > strNumChar[i]){
			minCharacterRepetitions = strNumChar[i];
		}
	}


	//array of tree leaves
	struct charNode *vectorNode = calloc(leaves,sizeof(struct charNode));
	for(int i = 0; i < leaves; i++){
		vectorNode[i].data = ' ';
	}
	createVectorOfLeaves(treeChar,vectorNode);


	//creation string that contain the second line output
	int size = ((leaves - 1)  * (leaves ))/2;
	char *outputSecondLine = malloc(size * 7); 


////////////First Line OUTPUT///////////////////////////////////////////////////////////
	printf("%d ",leaves);
	int countArch = 0;
	int k= 0;
	for(int i = 0; i < leaves-1;i++){
		for(int j = i+1; j < leaves;j++){
			k = compareDistanceLeaves(&vectorNode[i],&vectorNode[j],minCharacterRepetitions,maxCharacterRepetitions);
			countArch += k;
			//there is an arch from leave i to j
			if(k == TRUE){
				sprintf(outputSecondLine + strlen(outputSecondLine),"%c -- %c\n",vectorNode[i].data,vectorNode[j].data);
			}
		}
	}
	printf("%d\n",countArch);


////////////Second Line OUTPUT/////////////////////////////////////////////////////////
	printf("graph G {\n");
	//label
	for (int i = 0; i < leaves; i++){
		printf("%c [label = \"%d\"];\n",vectorNode[i].data,i);
	}
	//arches
	printf("%s",outputSecondLine);

	printf("}\n");


	//free memory
	free(vectorNode);
	free(outputSecondLine);
	destroy(treeChar);
	
	return 0;
}
