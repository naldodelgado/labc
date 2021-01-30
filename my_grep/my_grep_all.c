#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE_SIZE 9999
char* file;

int active [] = {0,0,0,0};//check if options -l, -i, -c and -v are activated
int act = 0;//check if one of the options is activated

int my_getOption(char* st);
int is_option(char* st);

void grep_option(char* word,FILE* fp);

void lgrep(char* word,FILE* fp);
void cgrep(char* word,FILE* fp);
void igrep(char* word,FILE* fp);
void vgrep(char* word,FILE* fp);
void grep(char* word,FILE* fp);

int verify(char *str, char* word);//verify if the line contain the word
int verify_i(char *str, char *word);//verify if the line contain the word ---- uppercase or lowercase doesn't matter

int main(int argc, char** argv){
  char* word;
  FILE * fp;
  int opt;
  
  if(argc==1){
    printf("Utilização: ./my_grep [OPÇÃO]... PADRÃO [FICHEIRO]...\n");
    exit(-1);
  }
  
  if(argc==2){
    file = "(standard input)";
    word = argv[1];
    grep(word,stdin);
    exit(0);
  }

  for(int i =1; is_option(argv[i]); i++)
    opt= my_getOption(argv[i])+i-1;

  if(!act)
    opt = 1;
  
  word = argv[opt];
  
  if(opt==argc-1){
    file = "(standard input)";
    grep_option(word,stdin);
    exit(0);
  }
  for(int i=opt+1; i<argc; i++){
    if(strcmp(argv[i],"-") == 0){
      fp=stdin;
      file = "(standard input)";
    }
    else{
      fp=fopen(argv[i],"r");
      file = argv[i];
    }
    grep_option(word,fp);    
  }
}

int is_option(char* st){
  if(st[0]=='-')
    return 1;
  else
    return 0;
}

int my_getOption(char* st){
  int pos=1;
  char ch;
  int i=1;
  if(st[0]=='-' && strlen(st)>1)
    while(i<strlen(st)){
      ch=st[i];
      switch(ch){
      case 'l':{active[0]=1; act++; pos=2; break;}
      case 'i':{active[1]=1; act++; pos=2; break;}
      case 'c':{active[2]=1; act++; pos=2; break;}
      case 'v':{active[3]=1; act++; pos=2; break;}
      }
      i++;
    }
  return pos;
}

void grep_option(char* word,FILE* fp){
  if(active[0])//-l
    lgrep(word,fp);
  else if(active[2])//-c
    cgrep(word,fp);
  else if(active[1])//-i
    igrep(word,fp);
  else if(active[3])//-v
    vgrep(word,fp);
  else//empty
    grep(word,fp);
}

void grep(char* word,FILE* fp){
  char str[MAX_LINE_SIZE];
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL)
    if(verify(str,word))
      printf("%s",str);
  fclose(fp);
}

void igrep(char* word,FILE* fp){
  char str[MAX_LINE_SIZE];
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
    if(active[3]){//-v
      if(!verify_i(str,word))
	printf("%s",str);
    }
    else
      if(verify_i(str,word))
	printf("%s",str);
  }
  fclose(fp);
}

void vgrep(char* word,FILE* fp){
  char str[MAX_LINE_SIZE];
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL)
    if(!verify(str,word))
      printf("%s",str);
  fclose(fp);
}

void cgrep(char* word,FILE* fp){
  char str[MAX_LINE_SIZE];
  int i=0;
  //op i in active[1] 
  //op v in active[3]
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
    if(active[3]){
      if (active[1]){//-civ
	if(!verify_i(str,word))
	  i++;
      }
      else//-cv
	if(!verify(str,word))
	  i++;
    }
    else if (active[1]){//-ci
      if(verify_i(str,word))
	i++;
    }
    else//-c
      if(verify(str,word))
	i++;
  }
  printf("%d\n",i);
  fclose(fp);
}

void lgrep(char* word,FILE* fp){
  char str[MAX_LINE_SIZE];
  int i=0;
  //op i in active[1] 
  //op v in active[3]
  while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
    if(active[3]){
      if (active[1]){//-liv
	if(!verify_i(str,word))
	  i=1;
      }
      else//-lv
	if(!verify(str,word))
	  i=1;
    }
    else if (active[1]){//-li
      if(verify_i(str,word))
	i=1;
    }
    else//-l
      if(verify(str,word))
	i=1;
  }
  if(i)
    printf("%s\n",file);
  fclose(fp);
}

int verify(char *str, char *word){
  char *aux = (char*) malloc(strlen(word));
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

int verify_i(char *str, char *word){
  char *aux = (char*) malloc(strlen(word));
  char *staux = (char*) malloc(strlen(str));
  
  for(int k=0; k < strlen(word); k++)
    word[k]=toupper(word[k]);

  for(int k=0; k < strlen(str); k++)
    staux[k]=toupper(str[k]);
  
  int i=0,j=0;

  while(i < strlen(str)){
    if(staux[i] == word[j]){
      aux[j] = staux[i];
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