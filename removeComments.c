#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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


int main(int argc,char ** argv){
    char testcase[50];
    strcpy(testcase,"testcases/");
    strcat(testcase,argv[1]);
    FILE * f1;
    FILE *main_file;
    main_file = fopen(testcase,"r");
    f1 = fopen("cleanFile.txt","w");
    int flag = 0;
    
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
