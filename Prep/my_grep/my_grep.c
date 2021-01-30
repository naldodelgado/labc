#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#define MAX_LINE_SIZE 10000

int options[4]= {0,0,0,0}; // it stores the activation of the files
int specify; // it says if the program prints the name of the <file> before the content

void grep(char* word, char* file);
int check(char* str, char* word);
char* tolowerCase(char* str);
void checkCorruption(void);

int main(int argc, char** argv){
  int c;
  char* word = argv[1];
  if(argc>=4){specify=1;}

  while((c=getopt(argc,argv,"licv")) !=-1){
    switch (c){
    case 'l' :{options[0]=1 ; break;} // file names only
    case 'i' :{options[1]=1 ;break;}  // ignore CAP 
    case 'c' :{options[2]=1 ;break;} // number of lines <word> appears on each file
    case 'v' :{options[3]=1 ;break;} // reverse
    }
  }
  puts("OK");
  checkCorruption();
  for(int i = 2; i<argc;i++){
	  puts(argv[2]);
  	grep(word,argv[i]);
  }
	return 0;
}

void checkCorruption(void){
  if(options[0] == 1 && (options[1] == 1 || options[2] == 1)) // -l can't combine with c or i
    exit(-1);
}

void grep(char* word, char* file){
	char str[MAX_LINE_SIZE];
	FILE* fp = fopen(file,"r");
	
	int counter = 0; // this is used only when -c is activated
	while(fgets (str, MAX_LINE_SIZE, fp) != NULL){
		if(!(options[0] && options[2] && options[3]))
			if(check(str,word))
				puts(str);
		if(options[0] ){ // reverse && filenames
			if(options[3]){
    				if(!check(str,word))
					puts(file);
			}
			else{
				if(check(str,word))
					puts(file);
			}
		}
		if(options[2] ){
			if(options[3] ){
				if(!check(str,word))
					counter ++;
			}
			else{
				if(check(str,word))
					counter++;
			}		
		}
	}
	if(counter)
		printf("<%s>:%d\n",file,counter);
 	
  fclose(fp);
}

int check(char* str, char* word){
	 puts("OK");
  char *aux =(char*)malloc(strlen(word));
  if(options[1] && strlen(str) && strlen(word)){ // ignore caps
	str = tolowerCase(str);
	word = tolowerCase(word);
  }
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

char* tolowerCase(char* str){
	int size = strlen(str);
	for(int i = 0; i<size; i++){
		str[i] = tolower(str[i]);
	}
	return str;
}