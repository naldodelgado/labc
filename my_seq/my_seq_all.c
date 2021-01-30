#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX(A,B) (A)>(B)?(A):(B)
#define NUM(A) (A)>='0' &&  (A)<='9'

char* file;
int prec;//precision
int siz;//size of the output
int active [] = {0,0,0};//check if options -s, -w and -f are activated
int act = 0;//check if one of the options is activated
char* s_sep;

int my_getOption(char* st);
int is_option(char* st);

void seq(int last);
void seq_(int first, int last);
void seq__(int first, int inc, int last);

int max_size(char* first, char* second);
int size_n(char* str);


int main(int argc, char** argv){
  int opt = 1;
  int argNum;
  
  file = argv[0];

  if(argc==1){
    printf("%s: operando em falta\n",file);
    exit(-1);
  }
   
  for(int i =1; is_option(argv[i]); i++){
    opt= my_getOption(argv[i])+i-1;
    argNum = argc - opt;
    if(!argNum){
      printf("%s: operando em falta\n",file);
      exit(-1);
    }
  }
  
  if(active[0] && active[2]){
    printf("%s: mau uso de -s e -f\n",file);
    exit(-1);
  }
  
  if(active[0]){
    s_sep = argv[opt];
    opt++;
  }
    
  argNum = argc - opt;
 
  switch(argNum){
  case 0:{
    printf("%s: operando em falta\n",file);
    break;
  }
  case 1:{
    siz = max_size(argv[opt],"0");
    seq(atof(argv[opt]));
    break;
  }
  case 2:{
    siz = max_size(argv[opt],argv[opt+1]);
    seq_(atoi(argv[opt]),atoi(argv[opt+1]));
    break;
  }
  case 3:{
    siz = max_size(argv[opt],argv[opt+2]);
    seq__(atoi(argv[opt]),atoi(argv[opt+1]),atoi(argv[opt+2]));
    break;
  }
  default: {
    printf("%s: operando extra «%d»\n",file,argNum);
    break;
  }
  }
}

void seq(int last){
  int i=1;
  while(i <= last-1){
    if(active[0]){
      if(active[1])
	printf("%0*d%s",siz,i,s_sep);
      else
	printf("%d%s",i,s_sep);    
    }
    else 
      if(active[1])
	printf("%0*d\n",siz,i);
      else
	printf("%d\n",i);    
    i++;
  }
  if(active[1])
    printf("%0*d\n",siz,i);
  else
    printf("%d\n",i);
}

void seq_(int first, int last){
  int i=first;
  while(i <= last-1){
    if(active[0]){
      if(active[1])
	printf("%0*d%s",siz,i,s_sep);
      else
	printf("%d%s",i,s_sep);    
    }
    else 
      if(active[1])
	printf("%0*d\n",siz,i);
      else
	printf("%d\n",i);
    i++;
  }
  if(active[1])
    printf("%0*d\n",siz,i);
  else
    printf("%d\n",i);
}

void seq__(int first, int inc, int last){
  if(inc == 0){
    printf("%s: invalid Zero increment value\n",file);
    exit(-1);
  }
  int i=first;
  if(inc > 0){
    while(i <= last-inc){
      if(active[0]){
	if(active[1])
	  printf("%0*d%s",siz,i,s_sep);
	else
	  printf("%d%s",i,s_sep);    
      }
      else 
	if(active[1])
	  printf("%0*d\n",siz,i);
	else
	  printf("%d\n",i);
      i+=inc;
    }
  }
  if(inc < 0){
    while(i >= last-inc){
      if(active[0]){
	if(active[1])
	  printf("%0*d%s",siz,i,s_sep);
	else
	  printf("%d%s",i,s_sep);    
      }
      else 
	if(active[1])
	  printf("%0*d\n",siz,i);
	else
	  printf("%d\n",i);
      i+=inc;
    }
  }
  if(active[1])
    printf("%0*d\n",siz,i);
  else
    printf("%d\n",i);
}

int is_option(char* st){
  if(st[0]=='-'){
    if(NUM(st[1]))
      return 0;
    return 1;
  }
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
      case 's':{active[0]=1; act++; pos=2; break;}
      case 'w':{active[1]=1; act++; pos=2; break;}
      case 'f':{active[2]=1; act++; pos=2; break;}
      default: {if(act) pos=2; break;}
      }
      i++;
    }
  return pos;
}

int max_size(char* first, char* second){
  return MAX(size_n(first),size_n(second));
}

int size_n(char* str){
  int flag = 0;
  int i = 0;
  int count = 0;
  char ch;
  while(i<strlen(str)){
    ch = str[i];
    if(!flag) count++;
    if(ch == '.') flag = 1;
    i++;
  }
  return count;
}