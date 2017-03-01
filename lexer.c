// Sugam Garg - 2014A7PS092P, Divish Dayal - 2014A7PS132P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashtable.h"
#include"queue.h"
#include<ctype.h>

void removeComments();
char *getStream();
void matcher();
void addToQueue();


short flag = 0;
static FILE * main_file;




FILE * fp;
static int line_number = 0;

int main(int argc,char ** argv){
    struct queue * Q;
    Q = creatQueue();
    
    char testcase[50];
    strcpy(testcase,"testcases/");
    strcat(testcase,argv[1]);
    //printf("working");
    removeComments(testcase,"cleanfile.txt");
    //printf("working");
    fp = fopen("tokens.txt","w");
    FILE * cf;
    FILE *keyfp = fopen("keywords.txt","r");
    struct firstDataItem *ht = createHashTable(16);
        while(1){
            int number;
            char str[13];
            fscanf(keyfp,"%d %s",&number,str);
            insert(str, number, ht);
            if (feof(keyfp))
                break;
            
        }
    
    cf = fopen("cleanfile.txt","r");
    
    while(1){
        char str[100];
        strcpy(str,getStream(cf));
        line_number++;
        //printf("%s\n",str);
        if(strcmp(str,"") == 0){
            break;
        }
        else{
            matcher(str,ht,Q);
        }
    }
    //printQ(Q);
}

void matcher(char *buf,struct firstDataItem *ht,struct queue *Q){
    int i = 0;
    int length = strlen(buf);
    char ch = buf[i];
    
    while(i < length){
        //printf("lookahead is : %c\n",ch);
        if(ch == '+'){
            fprintf(fp," PLUS");
            addToQueue(Q,"PLUS",50,"\0");
            
        }
        else if(ch == '-'){
            fprintf(fp," MINUS");
            addToQueue(Q,"MINUS",51,"\0");
        }
        else if(ch == '/'){
            fprintf(fp," DIV");
            addToQueue(Q,"DIV",52,"\0");
        }
        else if(ch == '*'){
            if(buf[i+1] != '\0' && buf[i+1] == '*'){
                fprintf(fp," COMMENTMARK");
                addToQueue(Q,"COMMENTMARK",53,"\0");
                i = i + 2;
                if(flag == 1){
                    flag = 0;
                    continue;
                }
                else{
                    flag = 1;
                }
                while (!((buf[i] == '*')&&(buf[i+1]=='*'))&&(i < length)) {
                    i++;
                }
                i--;
            }
            else{
                fprintf(fp," MUL");
                addToQueue(Q,"MUL",54,"\0");
            }
        }
        
        else if(ch == '<'){
            if(buf[i+1] != '\0' && buf[i+1] == '='){
                fprintf(fp," LE");
                addToQueue(Q,"LE",55,"\0");
                i++;
            }
            else if(buf[i+1] != '\0' && buf[i+1] == '<'){
                fprintf(fp," DEF");
                addToQueue(Q,"DEF",56,"\0");
                i++;
            }
            else{
                fprintf(fp," LT");
                addToQueue(Q,"LT",57,"\0");
            }
        }
        
        else if(ch == '>'){
            if(buf[i+1] != '\0' && buf[i+1] == '='){
                fprintf(fp," GE");
                addToQueue(Q,"GE",58,"\0");
                i++;
            }
            else if(buf[i+1] != '\0' && buf[i+1] == '>'){
                fprintf(fp," ENDDEF");
                addToQueue(Q,"ENDDEF",59,"\0");
                i++;
            }
            else{
                fprintf(fp," GT");
                addToQueue(Q,"GT",60,"\0");
            }

        }
        else if(ch == '='){
            if(buf[i+1] != '\0' && buf[i+1] == '='){
                fprintf(fp," EQ");
                addToQueue(Q,"EQ",61,"\0");
                i++;
            }
        }
        else if(ch == '!'){
            if(buf[i+1] != '\0' && buf[i+1] == '='){
                fprintf(fp," NE");
                addToQueue(Q,"NE",62,"\0");
                i++;
            }
        }
        else if(ch == ':'){
            if(buf[i+1] != '\0' && buf[i+1] == '='){
                fprintf(fp," ASSIGNOP");
                addToQueue(Q,"ASSIGNOP",63,"\0");
                i++;
            }
            else{
                fprintf(fp," COLON");
                addToQueue(Q,"COLON",64,"\0");
            }
        }
        else if(ch == '.'){
            if(buf[i+1] != '\0' && buf[i+1] == '.'){
                fprintf(fp," RANGEOP");
                addToQueue(Q,"RANGEOP",65,"\0");
                i++;
            }
        }
        else if(ch == ';'){
            fprintf(fp," SEMICOL");
            addToQueue(Q,"SEMICOL",66,"\0");
        }
        else if(ch == ','){
            fprintf(fp," COMMA");
            addToQueue(Q,"COMMA",67,"\0");
        }
        else if(ch == '['){
            fprintf(fp," SQBD");
            addToQueue(Q,"SQBD",68,"\0");
        }
        else if(ch == ']'){
            fprintf(fp," SQBC");
            addToQueue(Q,"SQBC",69,"\0");
        }
        else if(ch == '('){
            fprintf(fp," BO");
            addToQueue(Q,"BO",70,"\0");
        }
        else if(ch == ')'){
            fprintf(fp," BC");
            addToQueue(Q,"BC",71,"\0");
        }
        else if(  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
            
            char string[20] = "";
            int j = 0;
            
            string[j++] = ch;
            i++;
            while( ( ( buf[i] >= 'a' && buf[i] <= 'z') || ( buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= '0' && buf[i] <= '9') || (buf[i] == '_') ) && buf[i] != '\n') {
                string[j++] = buf[i++];
            }
            i--;
            int keyword_number = search(string,ht);
            if(keyword_number >= 0){
                fprintf(fp," ");
                int k;
                char upper_string[20] = "";
                for(k = 0; k < strlen(string); k++){
                    fprintf(fp,"%c",toupper(string[k]));
                    upper_string[k] = toupper(string[k]);
                }
                addToQueue(Q,upper_string,keyword_number,"\0");
            }
            else{
                if(strlen(string) <= 8){
                    fprintf(fp," ID");
                    addToQueue(Q,"ID",49,string);
                }
                else{
                    printf("error");
                }
            }
            
        }
        else if(ch >= '0' && ch <= '9'){
            char num_string[20] = "";
            int h = 0;
            
            num_string[h++] = ch;
            i++;
            while (buf[i] >= '0' && buf[i] <= '9' && buf[i] != '\0') {
                num_string[h++] = buf[i++];
            }
            if(buf[i++] == '.'){
                if(buf[i] == '.'){
                    i = i - 2;
                    fprintf(fp," NUM");
                    addToQueue(Q,"NUM",48,num_string);
                    //printf("%d this is %c\n",line_number,buf[i]);
                }
                else if(buf[i] >= '0' && buf[i] <= '9'){
                    while (buf[i] >= '0' && buf[i] <= '9' && buf[i] != '\0') {
                        num_string[h++] = buf[i++];
                    }
                    if(buf[i] == 'E' || buf[i] == 'e'){
                        num_string[h++] = buf[i++];
                        if(buf[i] == '+' || buf[i] == '-' || (buf[i] >= '0' && buf[i] <= '9')){
                            num_string[h++] = buf[i++];
                            while (buf[i] >= '0' && buf[i] <= '9' && buf[i] != '\0') {
                                num_string[h++] = buf[i++];
                            }
                            fprintf(fp," RNUM");
                            addToQueue(Q,"RNUM",47,num_string);
                            i--;
                            //printf("%d this is %c\n",line_number,buf[i]);
                        }
                    }
                    else{
                        i--;
                        fprintf(fp," RNUM");
                        addToQueue(Q,"RNUM",47,num_string);
                        //printf("%d this is %c\n",line_number,buf[i]);
                    }
                }
            }
            else if(buf[i] == 'E' || buf[i] == 'e'){
                num_string[h++] = buf[i++];
                if(buf[i] == '+' || buf[i] == '-' || (buf[i] >= '0' && buf[i] <= '9')){
                    num_string[h++] = buf[i++];
                    while (buf[i] >= '0' && buf[i] <= '9' && buf[i] != '\0') {
                        num_string[h++] = buf[i++];
                    }
                    fprintf(fp," RNUM");
                    addToQueue(Q,"RNUM",47,num_string);
                    i--;
                    //printf("%d this is %c\n",line_number,buf[i]);
                }
            }
            else{
                fprintf(fp," NUM");
                addToQueue(Q,"NUM",48,num_string);
                i = i - 2;
                //printf("%d this is %c\n",line_number,buf[i]);
            }
        }
        else if(buf[i] == '\n'){
            fprintf(fp,"\n");
        }
        else if(buf[i] != ' ' && buf[i] != '\t' && buf[i] != '\r' && buf[i] != '\0'){
            printf("\nInvalid symbol '%c' at line %d, column %d\n",buf[i],line_number, i+1);
            fprintf(fp," _!!_");
        }
        i++;
        while (buf[i] == ' ' || buf[i] == '\t') {
            i++;
        }
        ch = buf[i];
    }
}

void addToQueue(struct queue *Q,char * keyword,int keyword_number,char * value){
            struct node *temp;
    
            temp = (struct node *)malloc(sizeof(struct node));
    
            strcpy(temp->id,keyword);
    
            strcpy(temp->value,keyword);
    
            temp->line_no = line_number;
    
            temp->id_no = keyword_number;
    
            temp->next = NULL;
            
            Enqueue(Q,temp);
    
    
    
    
}

char *getStream(FILE * gsfp){              //Get line from input file into memory
    char *str = (char *) malloc(100 * sizeof(char));
    fgets(str,100,gsfp);
    if(feof(gsfp))
        return str;
    if (strlen(str) == 100){
        int index = 99;
        while(!(str[index] == ' ' || str[index] == '\t')){
            index--;
        }
        str[index+1] = '\0';
        fseek(gsfp,-(99-index),SEEK_CUR);
    }	
    return str;
}



void removeComments(char *testcaseFile,char * cleanFile){

    FILE * f1;
    main_file = fopen(testcaseFile,"r");
    f1 = fopen(cleanFile,"w");
    
    
    while (1) {
        char buf[100] = "";
       strcpy(buf,getStream(main_file));
        //printf("the string is : %s\n",buf);
       if(strcmp(buf,"") != 0){
           int i = 0;
           int length = strlen(buf);
           while(i < length){
               //printf("Flag is : %d\n",flag);
               if(flag == 1){
                   while(i < length && !((buf[i]=='*')&&(buf[i+1]=='*'))){
                       i++;
                   }
               }
               //printf("While cond : %d  %d   %c   %c",i,length,buf[i],buf[i+1]);
               while(i < length && !((buf[i]=='*')&&(buf[i+1]=='*'))){
                   //printf("Chutiya pranav\n");
                   fprintf(f1,"%c",buf[i]);
                   i++;
               }
               //printf("This is : %c%c\n",buf[i],buf[i+1]);
               if(i != length){
                   i = i + 2;
                   if(flag == 1){
                       flag = 0;
                       continue;
                   }
                   else{
                       flag = 1;
                       continue;
                   }
                   
               }
           }
       }
       else{
           break;
       }
    
    }
    fclose(f1);
}
