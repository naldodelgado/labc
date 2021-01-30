#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_SIZE 9999

int m,n,stdinFlag = 0;
char ch;
char str[MAX_LINE_SIZE];

void slice(char* file);

int main(int argc, char **argv){
	if(argc<3){exit(-1);} // argumentos insuficientes

	m = atoi(argv[1]); n = atoi(argv[2]); //os limites de pesquisa
	char* file = argv[argc-1]; // escolhi argc-1 para ignorar tudo o que vem entre <n> e <file> uma vez que file deve ser o último argumento
	if(strcmp(file,"-") == 0 || argc == 3){stdinFlag =1;} // read from stdin

	if(m==n){return 0;}//print nothing
	if(m>n){puts("Argumentos trocados?");exit(0);}
	slice(file);
	return 0;
}

void slice(char* file){
	FILE * f;
	int counter = 0;
	/* PRINTING FROM STDIN */
	if(stdinFlag){
		f = stdin;
		int i = 0;
		while((ch = fgetc(f))!= EOF ){
			if(counter>=m-1 && counter<=n-2){ // allowed to print the lines
				if(counter == n-1){   // esta cadeia de 2 if só servem para garantir que o último '\n' não seja imprimido
					if(ch!='\n')
						str[i] = ch;
				}
				else{
					str[i] = ch;
				}
			}
			if(ch == '\n')
				counter ++;
			i++;
		}
		if(stdinFlag){puts(str);} // mostro o output só agora
	}

	/* PRINTING FROM <file> */
	else{
		f = fopen(file,"r");
		while((ch = fgetc(f))!= EOF ){
			if(counter>=m-1 && counter<=n-2){ // allowed to print the lines
				if(counter == n-1){   // esta cadeia de 2 if só servem para garantir que o último '\n' não seja imprimido
					if(ch!='\n')
						printf("%c",ch);
				}
				else{
					printf("%c",ch);
				}
			}
			if(ch == '\n')
				counter ++;
		}
		if(stdinFlag){puts(str);} // mostro o output só agora
	}
}