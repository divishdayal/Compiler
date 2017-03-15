// Sugam Garg - 2014A7PS092P, Divish Dayal - 2014A7PS132P

#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"hashtable.h"

extern void removeComments(char *testcaseFile,char * cleanFile);
extern char *getStream(FILE * gsfp);
extern void matcher(char *buf,struct firstDataItem *ht,struct queue *Q);
extern void addToQueue(struct queue *Q,char * keyword,char *lexeme,int keyword_number);
extern void generateTokens(struct queue *Q,struct firstDataItem *ht);
extern void populateHashTable(struct firstDataItem *ht);
extern struct node * getNextToken(struct queue *Q);
