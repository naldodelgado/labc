#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define MAX_LINE_SIZE 1000

char* toUpperCase(char* str){
    int i = 0;
    while(i <= strlen(str)){
        str[i] = toupper(str[i]);
        i++;
    }
    return str;
}

void printerr(int err){
    switch (err){
        case 1:
            puts("Too few arguments");break;
        case 2:
            puts("Ivalid option");break;
    }
}

int check(char *str, char *word){
  
  char *aux =(char*)malloc(strlen(word));
  int i=0,j=0;
  while(i < strlen(str)){
    if(str[i] == word[j]){
      aux[j] = str[i];
      j++;
    }
    else
      j = 0;
    i++;
  }
  if(strcmp(aux,word)==0)
    return 1;
  return 0;
}

void stgrep(char* word){
  char str[MAX_LINE_SIZE];
  int i = 0;
  while(fgets (str, MAX_LINE_SIZE, stdin) != NULL){
      str = toUpperCase(str);
    if( check(str,word) && i == 0){
      printf("(standard input)\n");
      i++;
    }
  }
}

void grep(char* word,char* file){
  char str[MAX_LINE_SIZE];
  FILE* fp = fopen(file,"r");
  int i = 0;
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
      str = toUpperCase(*str);
    if( check(str,word) && i == 0){
      printf("%s\n",file);
      i++;
    }
  }
  fclose(fp);
}

int main(int argc, char** argv){
    char* word = toUpperCase(argv[2]);
    if(argc < 4){
        stgrep(word);
        exit(0);
    }
    int lflag = 0;
    int option;
    while((option = getopt(argc,argv,"lc"))!=-1){
        switch(option){
            case 'l':
                lflag++;
                for(int i = 3; i < argc; i++){
                    char* file = argv[i];
                    if(strcmp(file,"-") == 0)
                        stgrep(word);
                    else
                        grep(word,file);
                }
                break;
            default:
                printerr(2);
                break;
        }

    }
    return 0;
}