#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(A,B) (A)>(B)?(A):(B)

char* file;
int prec;//precision

void seq(double last);
void seq_(double first, double last);
void seq__(double first, double inc, double last);
int max_decimals(char* first, char* second);
int n_decimals(char* str);

int main(int argc, char** argv){
  file = argv[0];
  switch(argc){
  case 1:{printf("%s: operando em falta\n",file); break;}
  case 2:{seq(atof(argv[1])); break;}
  case 3:{prec=max_decimals(argv[1],"0"); seq_(atof(argv[1]),atof(argv[2])); break;}
  case 4:{prec=max_decimals(argv[1],argv[2]); seq__(atof(argv[1]),atof(argv[2]),atof(argv[3])); break;}
  default: {printf("%s: operando extra «%d»\n",file,argc-1); break;}
  }
}

void seq(double last){
  int i=1;
  while(i <= last){
    printf("%d\n",i);
    i++;
  }
}

void seq_(double first, double last){
  double i=first;
  while(i <= last){
    printf("%.*f\n",prec,i);
    i++;
  }
}

void seq__(double first, double inc, double last){
  if(inc == 0){
    printf("%s: invalid Zero increment value\n",file);
    exit(-1);
  }
  double i=first;
  if(inc > 0){
    last += 0.000001;
    while(i <= last){
      printf("%.*f\n",prec,i);
      i+=inc;
    }
  }
  if(inc < 0){
    last -= 0.000001;
    while(i >= last){
      printf("%.*f\n",prec,i);
      i+=inc;
    }
  }
}

int max_decimals(char* first, char* second){
  return MAX(n_decimals(first),n_decimals(second));
}

int n_decimals(char* str){
  int flag = 0;
  int i = 0;
  int count = 0;
  char ch;
  while(i<strlen(str)){
    ch = str[i];
    if(flag) count++;
    if(ch == '.') flag = 1;
    i++;
  }
  return count;
}