// Sugam Garg - 2014A7PS092P, Divish Dayal - 2014A7PS132P

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"hashtable.h"
#include"queue.h"

void removeComments(char *testcaseFile,char * cleanFile);
char *getStream();

short flag = 0;
static FILE * main_file;

FILE * fp;
int main(){
    removeComments("abc.txt","a.txt");
    fp = fopen("tokens.txt","w");
}

void matcher(char *buf){
    int i = 0;
    int length = strlen(buf);
    char ch = buf[i];
    
    while(i < length){
        
        if(ch == '+'){
            fprintf(fp,"PLUS");
            
        }
        else if(ch == '-'){
            fprintf(fp,"MINUS");
        }
        else if(ch == '/'){
            fprintf(fp,"DIV");
        }
        else if(ch == '*'){
            if(buf[i+1] == '*'){
                fprintf(fp,"COMMENTMARK");
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
                fprintf(fp,"MUL");
            }
        }
        
        else if(ch == '<'){
            if(buf[i+1] == '='){
                fprintf(fp,"LE");
                i++;
            }
            else if(buf[i+1] == '<'){
                fprintf(fp,"DEF");
                i++;
            }
            else{
                fprintf(fp,"LT");
            }
        }
        
        else if(ch == '>'){
            if(buf[i+1] == '='){
                fprintf(fp,"GE");
                i++;
            }
            else if(buf[i+1] == '>'){
                fprintf(fp,"ENDDEF");
                i++;
            }
            else{
                fprintf(fp,"GT");
            }

        }
        else if(ch == '='){
            if(buf[i+1] == '='){
                fprintf(fp,"EQ");
                i++;
            }
        }
        else if(ch == '!'){
            if(buf[i+1] == '='){
                fprintf(fp,"NE");
                i++;
            }
        }
        else if(ch == ':'){
            if(buf[i+1] == '='){
                fprintf(fp,"ASSIGNOP");
                i++;
            }
            else{
                fprintf(fp,"COLON");
            }
        }
        else if(ch == '.'){
            if(buf[i+1] == '.'){
                fprintf(fp,"RANGEOP");
                i++;
            }
        }
        else if(ch == ';'){
            fprintf(fp,"SEMICOL");
        }
        else if(ch == ','){
            fprintf(fp,"COMMA");
        }
        else if(ch == '['){
            fprintf(fp,"SQBD");
        }
        else if(ch == ']'){
            fprintf(fp,"SQBC");
        }
        else if(ch == '('){
            fprintf(fp,"BO");
        }
        else if(ch == ')'){
            fprintf(fp,"BC");
        }
        else if(  (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
            
            char string[20] = "";
            int j = 0;
            string[j++] = ch;
            while( ( ( buf[i] >= 'a' && buf[i] <= 'z') || ( buf[i] >= 'A' && buf[i] <= 'Z') || (buf[i] >= '0' && buf[i] <= '9') || (buf[i] == '_') ) && buf[i] != '\n') {
                string[j++] = buf[i++];
            }
            
            
        }
        else if(ch >= '0' && ch <= '9'){
            while (buf[i+1] >= '0' && buf[i+1] <= '9') {
                <#statements#>
            }
        }
        index++;
        while (buf[i] == ' ' || buf[i] == '\t') {
            i++;
        }
        ch = buf[i];
    }
}

char *getStream(){              //Get line from input file into memory
    char *str = (char *) malloc(200 * sizeof(char));
    fgets(str,200,main_file);
    if(feof(main_file))
        return str;
    if (strlen(str) == 200){
        int index = 199;
        while(!(str[index] == ' ' || str[index] == '\t')){
            index--;
        }
        str[index+1] = '\0';
        fseek(main_file,-(199-index),SEEK_CUR);
    }	
    return str;
}



void removeComments(char *testcaseFile,char * cleanFile){

    FILE * f1;
    main_file = fopen(testcaseFile,"r");
    f1 = fopen(cleanFile,"w");
    
    
    while (1) {
        char buf[200] = "";
       strcpy(buf,getStream());
        printf("the string is : %s\n",buf);
       if(strcmp(buf,"") != 0){
           int i = 0;
           int length = strlen(buf);
           while(i < length){
               printf("Flag is : %d\n",flag);
               if(flag == 1){
                   while(i < length && !((buf[i]=='*')&&(buf[i+1]=='*'))){
                       i++;
                   }
               }
               printf("While cond : %d  %d   %c   %c",i,length,buf[i],buf[i+1]);
               while(i < length && !((buf[i]=='*')&&(buf[i+1]=='*'))){
                   printf("Chutiya pranav\n");
                   fprintf(f1,"%c",buf[i]);
                   i++;
               }
               printf("This is : %c%c\n",buf[i],buf[i+1]);
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
