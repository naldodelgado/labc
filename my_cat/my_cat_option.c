#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

struct x
{
  int n;
  int b; 
  int s;
  int shell;
  int counter;
  int ler;

};


void escreve( struct x* list, char ch, char ch1, int adj )
{
  if(ch=='\n'&& ch1=='\n' && adj==1 && (*list).s==1)
    return;
  if(ch=='\n' && (*list).n==1 && (*list).b!=1)
    {
      printf("%6d\t",(*list).counter);
      (*list).counter++;
    }

  else if(ch=='\n' && ch1!='\n' && (*list).b==1)
    {
      printf("%6d\t",(*list).counter);
      (*list).counter++;
    }

  putchar(ch1);
}

void readAndPrint( struct x* list, char str[] )
{
  char ch='\n';
  char ch1;
  int adj=0;
  (*list).ler++; 
  if ( str[0]=='-' ) // ou seja ler da shell
    {
      while( ( ch1=getc(stdin) ) != EOF )
	{
	  escreve( list, ch, ch1, adj );

	  if ( ch=='\n' && ch1== '\n' )
	    adj=1;
	  else
	    adj=0;

	  ch=ch1;
	}
    }

  else
    {
      FILE* read = fopen( str, "r" );

      while( ( ch1=getc(read) ) != EOF )
	{
	  escreve( list, ch, ch1, adj );

	  if ( ch=='\n' && ch1== '\n' )
	    adj=1;
	  else
	    adj=0;

	  ch=ch1;
	}
    }
}

// esta função busca as opçoes e guarda
void saveOption( struct x* list, int argc, char**argv )
{
  int option;

  while ( (option = getopt(argc, argv, "nbs")) != -1 )
    {
      switch ( option )
	{
	case 'n':
	  (*list).n=1;
	  break;

	case 'b':
	  (*list).b=1;
	  break;

	case 's':
	  (*list).s=1;
	  break;
	}
    }
}

int main(int argc, char** argv)
{
  struct x list = {0};
  list.counter=1;

  saveOption( &list, argc, argv );

  for ( int i=1; i<argc; i++ )
    {
      if ( argv[i][0]=='-' && argv[i][1]=='\0' )
	readAndPrint( &list, "-" );

      else if ( argv[i][0]!='-' )
        readAndPrint( &list, argv[i] );
    }
}
