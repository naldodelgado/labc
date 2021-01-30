#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,first,inc,last; // global variables
int flag; // 1 -> <inc> is negative || 0 -> <inc> is positive

void seq(int n, int f, int i, int l);
int filterError(void);

int main(int argc, char **argv){
  if(argc<3){exit(-1);} // exit faliure
  if(argc==3){ // first case
    n = atoi(argv[1]); // the MOD NUM
    first = 1; inc = 1; last = atoi(argv[2]);
  }
  if(argc==4){
	  n = atoi(argv[1]);
	  first = atoi(argv[2]); inc = 1; last = atoi(argv[3]);
  }
  if(argc==5){
	  n = atoi(argv[1]);
	  first = atoi(argv[2]); inc = atoi(argv[3]); last = atoi(argv[4]);
  }
  seq(n,first,inc,last);
  return 0;
}

void seq(int n, int f, int i, int l){
	if(filterError()){puts("ERROR");}
	if(!flag){ // inc positive
		while(f<=l){
			printf("%d\n",f%n);
			f+=i;
		}
	}
	if(flag){
		while(f>=l){
			printf("%d\n",f%n);
			f+=i;
		}
	}
}

int filterError(void){
	if(first>last && inc<=0){flag=1;return 0;}
	if(first<last && inc>=0){flag=0;return 0;}
	return 1;
}