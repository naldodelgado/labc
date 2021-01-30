#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat(FILE* fp){
    char ch;
	while((ch=fgetc(fp))!=EOF)
    	printf("%c",ch);
  	fclose(fp);
}

 void catToFile(char** argv, int argc, int start){
	 int destinationFile_index = argc - 1;
	 char ch;
	 char* destinationFile = argv[destinationFile_index];
	 char* originFile;
    	FILE *dest = fopen(destinationFile, "a");
	FILE *origin;
	    for(int i = start; i<destinationFile_index ; i++){
		    	originFile = argv[i];
			if(strcmp(originFile,"-") == 0){ // cat from stdin
				printf("\n\nCAT FROM <stdin> INTO <%s> ",destinationFile);
				while((ch=fgetc(stdin))!=EOF){
				fprintf(dest, "%c", ch);
				}
			}
			else{
				origin = fopen(originFile,"r");
				while((ch=fgetc(origin))!=EOF){
					fprintf(dest, "%c", ch);
				}
				ch = '\n';
				fprintf(dest, "%c", ch);
		    		fclose(origin);
			}
	    }
    	fclose(dest);
	 printf("\ncat completed succesfully\n");
 }

int main(int argc, char** argv){
	if(argc==1)
    	cat(stdin);

	for(int i=1;i<argc;i++){
		if(strcmp(argv[i],"-f") == 0){
			catToFile(argv,argc,i+1);
			exit(0);
		}
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
  return 0;
}
