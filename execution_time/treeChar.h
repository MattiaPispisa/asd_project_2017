#include <stdio.h>
#define TRUE 1
#define FALSE 0

struct charNode {
	char data;
	struct charNode *parent;
	struct charNode *left;
	struct charNode *right;
	int height;
	int isLeaf;
};


/*
	new node based on the lexicographical order of the key
	@param charNode root, MODIFY the srtuct in main function
	@param char x, VALID Char: a-z
	@param int i, node high
	@param int *leaves, MODIFY value in main function
	@return treeChar with new node
*/
struct charNode *treeCharInsert(struct charNode *treeChar,char x,int i,int *leaves);

/*
	create a new node
	@param char x, VALID Char: a-z
	@param int i, High of node
	@return new node x
*/
struct charNode *treeCharCreate(char x,int i);


 /*
 	array that contains pointers to the leaves
 	@param charNode root
 	@param array that will contains the leaves, MODIFY value in main function
 */
void createVectorOfLeaves(struct charNode *treeChar,struct charNode *vectorNode);


/*
	compare the distance of two difference node
	@param two charNode
*/
int compareDistanceLeaves(struct charNode *firstLeaf, struct charNode *secondLeaf,int min,int max);


/*
	destroy the tree from treeChar
	@param a node of treeChar
*/
void destroy(struct charNode *treeChar);