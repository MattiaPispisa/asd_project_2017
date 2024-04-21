#include <stdio.h>
#include <stdlib.h>
#include "treeChar.h"

struct charNode *treeCharCreate(char x,int i){
	struct charNode *nodeChar = malloc(sizeof(struct charNode));
	nodeChar->data = x;
	nodeChar->parent = NULL;
	nodeChar->left = NULL;
	nodeChar->right = NULL;
	nodeChar->height = i;
	nodeChar->isLeaf = TRUE;
	
	return nodeChar;
}


struct charNode *treeCharInsert(struct charNode *treeChar,char x,int i,int *leaves){
	if(treeChar == NULL){
		return treeCharCreate(x,i);
	}

	if(x <= treeChar->data){
		treeChar->left = treeCharInsert(treeChar->left,x,i+1,leaves);
		treeChar->left->parent = treeChar;
		if(treeChar->isLeaf == TRUE){
			treeChar->isLeaf = FALSE;
		}else if (treeChar->left->isLeaf == TRUE){
			*leaves += 1;
		}
	}else{
		treeChar->right = treeCharInsert(treeChar->right,x,i+1,leaves);
		treeChar->right->parent = treeChar;
		if(treeChar->isLeaf == TRUE){
			treeChar->isLeaf = FALSE;
		}else if (treeChar->right->isLeaf == TRUE){
			*leaves += 1;
		}
	}


	return treeChar;
}


void createVectorOfLeaves(struct charNode *treeChar, struct charNode *vectorNode){
	
	if(treeChar == NULL)
		return;

	if(treeChar->left == NULL && treeChar->right == NULL){
		int i = 0;
		while(TRUE){
			if(vectorNode[i].data == ' '){
				vectorNode[i] = *treeChar;
				break;
			}
			i++;
		}
		return;
	}

	createVectorOfLeaves(treeChar->left,vectorNode);
	createVectorOfLeaves(treeChar->right,vectorNode);
}


int compareDistanceLeaves(struct charNode *firstLeaf, struct charNode *secondLeaf,int min,int max){
	int count = 0;
	if(firstLeaf->height > secondLeaf->height){
		while( firstLeaf->height != secondLeaf->height && count <= max){
			firstLeaf = firstLeaf->parent;
			count++;
		}
	}else if( firstLeaf->height < secondLeaf->height){
		while(firstLeaf->height != secondLeaf->height  && count <= max){
			secondLeaf = secondLeaf->parent;
			count++;
		}
	}

	while (count <= max && firstLeaf->data != secondLeaf->data){
		count +=2;
		firstLeaf = firstLeaf->parent;
		secondLeaf = secondLeaf->parent;
	}

	if( count >= min && count <= max && firstLeaf->data == secondLeaf->data){
		return TRUE;
	}else{
		return FALSE;
	}
}


void destroy(struct charNode *treeChar){

	if(treeChar == NULL)
		return;

	struct charNode *l = treeChar->left;
	struct charNode *r = treeChar->right;
	free(treeChar);
	destroy(l);
	destroy(r);
}