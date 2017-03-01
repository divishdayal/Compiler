#ifndef _queueDef
#define _queueDef
struct node{
    
    char id[15];
    
    char value[50];
    
    int line_no;
    
    int id_no;
    
    struct node * next;
    
};


struct queue{
    
    int size;
    
    struct node *front, *end;
    
};
#endif
