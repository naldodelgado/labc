#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_BLANK(A) ((A)==' ' || (A)=='\n' || (A)=='\t')//check if is a blank charater
#define MAX(A,B) (A)>(B)?A:B

int sum_l=0;//sum lines
int sum_w=0;//sum words
int sum_b=0;//sum bytes
int L=0;//longest line length
int sum_files=0;
int active [] = {0,0,0,0};//check if options -l, -w, -c and -L are activated
int act = 0;//check if one of the options is activated
int n_act = 0;
void count(FILE* f);
void wc_empty();
void wc_file(char* file);
int my_getOption(char* stream);//my version of getopt for this problem

int main(int argc, char** argv){
  int ind;//index of the first file
  if(argc==1)
    wc_empty();
  else
    ind=my_getOption(argv[1]);

  if(!act){
    n_act = 1;
    for(int i=0;i<3;i++)
      active[i]=1;
  }
  for(int i =ind;i<argc;i++)
    wc_file(argv[i]);

  if(sum_files>1){
    if(active[0])
      printf("%d ",sum_l);
    if(active[1])
      printf("%d ",sum_w);
    if(active[2])
      printf("%d ",sum_b);
    if(active[3])
      printf("%d ",L);
    printf("total\n");
  }
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
      case 'w':{active[1]=1; act++; pos=2; break;}
      case 'c':{active[2]=1; act++; pos=2; break;}
      case 'L':{active[3]=1; act++; pos=2; break;}
      }
      i++;
    }
  return pos;
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
  n_act = 1;
  for(int i=0;i<3;i++)
    active[i]=1;
  count(stdin);
  printf("\n");
}

void count(FILE* f){
  int l=0;// lines
  int w=0;// words
  int b=0;// bytes
  int ll=0;// length
  int flag=0;
  char ch;
  while((ch=fgetc(f))!=EOF){
    b++;
    if(IS_BLANK(ch)){
      if(flag==1){
	w++;
	//ll++;
	flag=0;
      }
    }
    else flag=1;
    ll++;
    if(ch=='\n'){
      l++;
      L=MAX(L,ll-1);
      ll=0;
    }
  }

  if(flag==1) w++;

  sum_l+=l;
  sum_w+=w;
  sum_b+=b;
  sum_files++;

  if(n_act)
    printf("%d %d %d",l,w,b);
  else{
    if(active[0]){
      printf("%d",l);
      if(active[1] || active[2] || active[3])printf(" ");
    }
    if(active[1]){
      printf("%d",w);
      if(active[2] || active[3])printf(" ");
    }
    if(active[2]){
      printf("%d",b);
      if(active[3])printf(" ");
    }
    if(active[3]) printf("%d",L);
  }
}
