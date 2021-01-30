#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 1000


void stgrep(char* word);
void grep(char* word,char* file);
int check(char *line, char *word);


int main(int argc, char** argv){
  char* word = argv[1];
  if(argc==2)
    stgrep(word);
  
  for(int i=2; i<argc; i++){
    if(strcmp(argv[i],"-") == 0)
      stgrep(word);
    else
      grep(word,argv[i]);
  }
  return 0;
}

void stgrep(char* word){
  char str[MAX_LINE_SIZE];
  while(fgets (str, MAX_LINE_SIZE, stdin) != NULL){
    if( check(str,word))
      printf("%s",str);
  }
}

void grep(char* word,char* file){
  char str[MAX_LINE_SIZE];
  FILE* fp = fopen(file,"r");
 
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
    if( check(str,word))
      printf("%s",str);
  }
  fclose(fp);
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
