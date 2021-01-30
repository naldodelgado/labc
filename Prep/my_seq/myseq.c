#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char **argv){
  if(argc==2){
    int n = atoi(argv[1]);
    for(int i = 1; i<= n; i++){
      printf("%d\n",i);
    }
    exit(0);
  }
  if(argc == 3){
    int n = atoi(argv[1]);
    int nf = atoi(argv[2]);
    for(int i = n; i <=nf; i++){
      printf("%d\n",n);
      n++;
    }
  }
  else{
    int n = atoi(argv[1]), nf=atoi(argv[3]), inc = atoi(argv[2]);
    if(inc>0 && nf<n){exit(1);}
    if(inc<0 && nf>n){exit(1);}
      if(inc>0 && n<nf){
        while(n<=nf){
          printf("%d\n",n);
          n+=inc;
        }
      }
      else{
        while(n>=nf){
          printf("%d\n",n);
          n+=inc;
        }
      }
  }
  exit(0);
  return 0;
}