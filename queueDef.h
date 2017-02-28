#ifndef _queueDef
#define _queueDef
struct node{
    
    char id[100];
    
    int value;
    
    int line_no;
    
    struct node * next;
    
};


struct queue{
    
    int size;
    
    struct node *front, *end;
    
};
#endif
