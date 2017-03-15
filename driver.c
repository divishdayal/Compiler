// Sugam Garg - 2014A7PS092P, Divish Dayal - 2014A7PS132P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include"lexer.h"
#include"parseTable.h"
#include"parseTree.h"

#define AT 110

void createTree(g_node *grammar,struct table *T,struct queue * Q,char *elements[],char * filename){
    
    tree_node * root = tree_node_initialise(0);
    strcpy(root->name, elements[0]);
    tree_node *top = NULL;
    push(&top,AT,"@");
    
    push_node(&top,root);
    
//    push(&top,grammar[3].g_no,grammar[3].name);
//    push(&top,grammar[4].g_no,grammar[4].name);
//    push(&top,grammar[3].g_no,grammar[3].name);

    struct node* queue_node;
    queue_node = getNextToken(Q);
    
    
    while(1){
        
        if(top->num < NO_NON_TERM){
            char grammar_rule [10];
            //printf("%d  %d %d  th value of no is%d\n",top->num,queue_node->id_no,queue_node->id_no - NO_NON_TERM,NO_NON_TERM);
            strcpy(grammar_rule,T->cell[top->num][queue_node->id_no - NO_NON_TERM].rule);
            //printf("%s\n",grammar_rule);
            if(strcmp(grammar_rule,"") == 0){
                break;
            }
            char * str_tok = "-";
            char * token = strtok(grammar_rule, str_tok);
            int line_number = atoi(token);
            token = strtok(NULL, str_tok);
            int section_no = atoi(token);
            g_node * rule = grammar[line_number].next;
            int or_count = 1;
            while(rule != NULL){
                if(rule->g_no == OR_RULE)
                    or_count++;
                if(or_count == section_no)
                    break;
                rule = rule->next;
            }
            if(rule == NULL){
                printf("error occured : section not found");
                exit(EXIT_FAILURE);
            }
            if(rule->g_no == OR_RULE)
                rule = rule->next;
            int arr[10];
            for(int i= 0; i<10; i++){
                arr[i]= -1;
            }
            int count = 0;
            while(rule != NULL && rule->g_no != OR_RULE){
                arr[count++] = rule->g_no;
                rule = rule->next;
            }
        //    for(int i =0 ; i<10; i++){
        //        printf("%d", arr[i]);
        //    }
            count--;
            //printf("hello");
            //fflush(stdout);
            //tree_node * current_popped = top->node_tree;
//            printf("%s", current_popped->name);
//            fflush(stdout);
           tree_node * current_popped = pop(&top);
            
            while(count >= 0){
                //printf("%d\n",arr[count]);
                if(arr[count] != 106){
                    tree_node * new = tree_node_initialise(arr[count]);
                    strcpy(new->name, elements[arr[count]]);
                    push_node(&top,new);
                    //tree_node * new = tree_node_initialise(top->num);
                    //strcpy(new->name, elements[top->num]);
                    tree_insert_child(current_popped, new);
                    //in_order_traversal(root);
                    count--;
                }
                else{
                    break;
                }
                
            }
        }
        printStack(top);
        if(queue_node->id_no == top->num){
            pop(&top);
            queue_node = getNextToken(Q);
            printf("\n\n\n");
            printStack(top);
            
        }
        if(top->num == AT){
            printf("\n----------------- COMPILATION SUCCESSFUL -----------------\n");
            break;
        }
    }
    if(top->num != AT){
        printf("\n----------------- COMPILATION UNSUCCESSFUL -----------------\n");
    }
    
    printStack(top);
    FILE * fp = fopen(filename, "a");
    in_order_traversal(root,fp);
    fclose(fp);
}



void printCleanFile(){
    FILE *fp;
    fp = fopen("cleanfile.txt","r");
    while(1){
        char str[100];
        strcpy(str,getStream(fp));
        printf("%s",str);
        if(strcmp(str,"") == 0){
            break;
        }
    }

}


int main(int argc,char **argv){
    struct queue * Q;
    Q = creatQueue();
    
    removeComments(argv[1],"cleanfile.txt");
    
    
    struct firstDataItem *ht = createHashTable(16);
    populateHashTable(ht);
    
    
    char * elements[NO_ELE] = {"program","moduleDeclarations","moduleDeclaration","otherModules","driverModule","module","ret","input_plist","N1","output_plist","N2","dataType","type","moduleDef","statements","statement","ioStmt","var","whichId","simpleStmt","assignmentStmt","whichStmt","lvalueIDStmt","lvalueARRStmt","index","moduleReuseStmt","optional","idList","N3","expression","arithmeticOrBooleanExpr","N7","AnyTerm","N8","arithmeticExpr","N4","term","N5","factor","op1","op2","logicalOp","relationalOp","declareStmt","condionalStmt","caseStmts","N9","value","default","iterativeStmt","range",
                                "RANGEOP", "WHILE", "IN", "FOR", "DEFAULT", "FALSE", "TRUE", "BREAK", "CASE", "SWITCH", "NE", "EQ", "GE", "GT", "LE", "LT", "OR", "AND", "DIV", "MUL", "PLUS", "MINUS", "PARAMETERS", "WITH", "USE", "ASSIGNOP", "RNUM", "NUM", "PRINT", "BC", "BO", "END", "START", "OF", "ARRAY", "BOOLEAN", "REAL", "INTEGER", "COMMA", "COLON", "RETURNS", "SQBC", "SQBO", "INPUT", "TAKES", "ENDDEF", "DEF", "DRIVERENDDEF", "PROGRAM", "DRIVER", "DRIVERDEF", "SEMICOL", "ID", "MODULE", "DECLARE", "EPSILON", "GET_VALUE", "|", "$"};
    

    
    char * filename = "grammar.txt";
    g_node * grammar = parse_grammar(filename, elements);
    
    
    struct table *T;
    T = (struct table *)malloc(sizeof(struct table));
    createParseTable(T,grammar);
    
    generateTokens(Q,ht);

//    for(int i = 0 ; i < NO_NON_TERM;i++){
//                  for (int j = 0; j < NO_TERM + 1; j++) {
//                      if(strcmp(T->cell[i][j].rule,"") != 0)
//                          printf("the rule written at [%d][%d] is : %s\n",i,j,T->cell[i][j].rule);
//                  }
//              }
    
    
    
    printf("First and Follow sets automated\n");
    printf("Both lexical and syntax analysis modules implemented\n");
    printf("parse tree constructed\n\n\n\n\n");
    printf("Works for testcase1,3,4\n");
    
    while(1){
        
        printf("Press 1 : For removal of comments\n");
        printf("Press 2 : For printing the token list\n");
        printf("Press 3 : For parsing to verify the syntactic correctness of the input source code and printing parsetree\n");
        //printf("Press 4 : For creating the parse tree\n");
        printf("Press 5 : Exit\n");
        int input;
        scanf("%d",&input);
        if(input == 5){
            break;
        }
        switch (input) {
            case 1:
                printCleanFile();
                break;
                
            case 2:
                //fp = fopen("tokens.txt","w");
                printQ(Q);
                break;
            case 3 :
                createTree(grammar,T,Q,elements,argv[2]);
                break;
            case 4 :
                break;
        }
    }
    
    
}

