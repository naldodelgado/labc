#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat(FILE* fp){
  char ch;
  while((ch=fgetc(fp))!=EOF)
    printf("%c",ch);
  fclose(fp);
}

int main(int argc, char** argv){
  if(argc==1)
    cat(stdin);

  for(int i=1;i<argc;i++){
    if(strcmp(argv[i],"-")==0)
      cat(stdin);
    else{
      FILE* fp=fopen(argv[i], "r");
      if(fp==NULL){
	printf("./my_wc: <%s>: No such file or directory\n",argv[i]);
	exit(EXIT_FAILURE);
      }
      cat(fp);
    }
  }
}
