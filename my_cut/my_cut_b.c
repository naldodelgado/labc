#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define MAX_LINE_SIZE 1000

// for the -b option we need three options (3)
// for the -d option we need four options  (4)
// for the -f option we need four options  (4)

// the flollowing variables are auxiliar global variables
// these flags are the ones who are going to decide wich options were chosen
int fflag = 0;
int dflag = 0;
int bflag = 0;

void process(char *word, char *range, int capp);

void cutb(char *range,char *file);

int main(int argc, char **argv){
    int c;
    char* word = argv[4]; 
    char* file = argv[3];
    int capp = (strlen(word)); // "1,2,3,4,5" has 9 caracters but only need 5
    //printf("%d\n",capp);
    char range[capp];
    while((c = getopt(argc,argv,"bdf")) !=-1){
        switch(c){
            case 'b':
                bflag = 1; // setting on the b option
                process(word,range,capp); // process word into range using the capacity(capp) info
                break;
            case 'd':
                dflag = 1; // setting on the d option
                //process(word,range,capp); // process word into range using the capacity(capp) info
                break;
            case 'f':
                fflag = 1; // setting on the f option
                process(word,range,capp); // process word into range using the capacity(capp) info
                //puts("OK");
                cutb(range,file);
                break;
        }
    }

    return 0;
}

void process(char *word, char *range, int capp){
    //puts(word);
    //printf("%c\n",word[0]);
    //range[0] = word[0];
    int a = 0;
    for(int i = 0; i <= capp; i++){
        if(isdigit(word[i])){
            range[a] = word[i];
            a++;
        } 
    }
}

void cutb(char *range,char *file){
    char* str = malloc(MAX_LINE_SIZE * sizeof(char));
    FILE *fp = fopen(file,"r");
    int strsize = 0;
    char oi[20];
    oi[0] = 'c';
    printf("%c ",oi[0]);
    //printf("%d\n",strsize);
    //puts(range);
    int rangesize = strlen(range) - 1; // -1 to prevent segmentation fault
    //printf("%d\n", rangesize);
    while(!feof(fp)){
        fgets(str,MAX_LINE_SIZE,fp);
        strsize = strlen(str) - 1 ; // -1 to prevent segmentation fault
        printf("%d ",strsize);
        if(strsize<rangesize){ // to prevent segmentation fault in case the line from the file is too short, the the limit for i is linesize instead of rangesize
           for(int i = 0;i <= strsize; i++){
                char* c = &range[i];
                int n = atoi(c);
                printf("%c ",str[n]);
           } 
        }
        for(int i = 0;i <= rangesize; i++){
            char* c = &range[i];
            int n = atoi(c);
            printf("%c ",str[n]);
        }
    }
    fclose(fp);
    
}

/*
void grep(char* word,char* file){
  char str[MAX_LINE_SIZE];
  FILE* fp = fopen(file,"r");
  int i = 0;
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
    if( check(str,word) && i == 0){
      printf("%s\n",file);
      i++;
    }
  }
  fclose(fp);
}
*/
