#include<stdio.h>
#include<stdlib.h>
#include"queueDef.h"

extern struct queue *creatQueue();

extern void Enqueue(struct queue *Q,struct node *temp);

extern void Dequeue(struct queue *Q);

extern void printQ(struct queue *Q);
