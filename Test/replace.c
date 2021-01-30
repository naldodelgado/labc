#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 99999

char* original;
char*  rep;
char aux[500];
int stdinFlag = 0;
char toPrint[MAX_LINE_SIZE];

void cat(char* file){
  FILE* f = fopen(file,"r");
  char ch;
  while((ch=fgetc(f))!=EOF)
    printf("%c",ch);
  fclose(f);
}

void replace(char* file);
void concat(char* s, char* aux, int a);

int main(int argc, char **argv){
	if(argc<3){exit(-1);} // argumentos insuficientes

	original= argv[1]; 
	rep = argv[2]; // to switch
	char* file = argv[argc-1]; // escolhi argc-1 para ignorar tudo o que vem entre <string1> e <file> uma vez que file deve ser o último argumento
	if(strcmp(file,"-") == 0 || argc == 3){stdinFlag =1;} // read from stdin

	if(strcmp(original,rep)==0){cat(file);return 0;}
	replace(file);
	return 0;
}

void replace(char* file){
  char ch;
  int i = 0; int a = 0;int foccur = 0; int faccur = 0; // first equity occurency
  int size = strlen(original);
  FILE* f;
  if(stdinFlag){f=stdin;}
  else {f = fopen(file,"r");}
  while((ch = fgetc(f))!= EOF ){
    if(ch == original[i]){
      aux[i] = ch;
	 if(!foccur){
      	foccur = i; // store first occurency
		faccur = a;
	 }
      i++;
	 a++;
    }
    else{
      concat(toPrint,aux,a);
      i = 0;
      foccur = 0;
      a = ++faccur;
    }
    if( i ==  size) {// found one occurrency
	concat(toPrint,rep,foccur);
	a+=strlen(rep);
    }
}
puts(toPrint);
}

void concat(char* s, char* aux, int a){
  int i = strlen(aux);
  for(int j = 0; j<i;j++){
    s[a]=aux[j];
    a++;
  }
  return;
}