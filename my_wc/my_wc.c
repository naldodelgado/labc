#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//check if is a blank charater
#define IS_BLANK(A) ((A)==' ' || (A)=='\n' || (A)=='\t')

int sum_l=0; //sum lines
int sum_w=0; //sum words
int sum_b=0; //sum bytes
int sum_files=0;

void count(FILE* f);
void wc_empty();
void wc_file(char* file);

int main(int argc, char** argv){

  if(argc==1)
    wc_empty();
  int i;
  for(i=1;i<argc;i++)
    wc_file(argv[i]);
  if(sum_files>1)
    printf("%d %d %d total\n",sum_l,sum_w,sum_b);
}

void wc_file(char* file){
  FILE* f;
  if(strcmp(file,"-")==0)
    f=stdin;
  else{
    f=fopen(file, "r");
    if(f==NULL){
      printf("./my_wc: <%s>: No such file or directory\n",file);
      exit(EXIT_FAILURE);
    }
  }
  count(f);
  printf("\n");
  fclose(f);
}

void wc_empty(){
  count(stdin);
  printf("\n");
}

void count(FILE* f){
  int l=0; //lines
  int w=0; //words
  int b=0; //bytes
  int flag=0;
  char ch;

  while((ch=fgetc(f))!=EOF){
    b++;
    if(IS_BLANK(ch)){
      if(flag==1){
	w++;
	flag=0;
      }
    }
    else flag=1;
    if(ch=='\n')
      l++;
  }

  if(flag==1) w++;

  sum_l+=l;
  sum_w+=w;
  sum_b+=b;
  sum_files++;

  printf("%d %d %d",l,w,b);
}
