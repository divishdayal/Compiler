#include<stdio.h>
#include<stdlib.h>
#include"hashDef.h"

extern int search(char *keyword,struct firstDataItem *HT);
extern int hashValue(char *str);
extern void insert(char *keyword,int keyword_number,struct firstDataItem *HT);
extern struct firstDataItem *createHashTable(int size);
