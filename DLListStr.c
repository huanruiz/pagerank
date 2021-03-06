/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
 modified by huanrui zhang Jan 2019
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "DLListStr.h"

// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);
	
	strcpy(new->value, val);  // for int, new->value = it;
	
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLListStr
DLListStr newDLListStr()
{
	struct DLListRep *L;

	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}


/* 
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(DLListStr L, char *val){
	/* 
	   implement this function to
	   insert val in L  (in order), no duplicates (set)
	*/
	if(L == NULL) {
		return;
	}
	DLListNode *new = newDLListNode(val);
	if(DLListStrIsEmpty(L)) {
		L->first = new;
		L->last = new;
	} else {
		DLListNode *node;
		node = L->first;
		
		while(node != NULL && strcmp(val, node->value) > 0)	{
			node = node->next;
		}
		if(node && strcmp(node->value, val) == 0) {
			return;
		}
		if(node == NULL) {
			L->last->next = new;
    	    new->prev = L->last;
			new->next = NULL;
			L->last = new;
		} else if(node == L->first) {
			new->next = L->first;
			L->first->prev = new;
			L->first = new;
		} else {
			new->next = node;
			new->prev = node->prev;
			node->prev->next = new;
			node->prev = new;
		}
	}
	L->nitems++;
}

// find string at certion index
char *show_a_Str(DLListStr L, int n) {
	DLListNode *curr = L->first;
	while(n>0) {
		curr = curr->next;
		n--;
	}
	return curr->value;
}

// find the indx of a string
int show_Index(DLListStr L, char *s) {
	int n = 0;
	DLListNode *curr = L->first;
	while(curr->value != NULL && strcmp(curr->value, s)) {
		curr = curr->next;	
		n++;
	}
	return n;
}

// display items from a DLListStr, comma separated
void showDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		count++;
		if(count > 1) {
			fprintf(stdout,", ");
		}
		fprintf(stdout,"%s",curr->value);
	}
	fprintf(stdout,"\n");
}


// free up all space associated with list
void freeDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}

// add by huanrui: check whether the list is empty
int DLListStrIsEmpty(DLListStr L) {
	return (L->nitems == 0);
}

