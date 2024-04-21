#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "treeChar.h"
/*
	@param string a, VALID Char a-z
	@return |V|,|E|,leaves graph dot format
*/

int main(int argc, char **argv){
	//initialization
	int lenString = 0;
	int leaves = 0;
	if(argc > 1){
		lenString = strlen(argv[1]);
		leaves = 1;
	}
	int strNumChar[26] = {0}; //each location is the number of character repetitions 0 = a , 25 = z
	int value;
	struct charNode *treeChar = NULL;	
	

	//creation tree
	for(int i = 0; i < lenString; i++){
		treeChar = treeCharInsert(treeChar,argv[1][i],0,&leaves);
		value = ((int) argv[1][i])-97;
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
	int size = ((leaves - 1)  * (leaves))/2;
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
