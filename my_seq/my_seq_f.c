#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>

void seqf(char* format, float floor, float inc, float roof);

int main(int argc, char** argv){
    int c;
    char* format = argv[2];
    while((c = getopt(argc,argv,"f")) !=-1){
        switch(c){
            case 'f':
                if(argc == 4){
                    float roof = atof(argv[3]);
                    seqf(format,1,1,roof);
                    }
                if(argc == 5){
                    float floor = atof(argv[3]);
                    float roof = atof(argv[4]);
                    seqf(format,floor,1,roof);
                    }
                if(argc == 6){
                    float floor = atof(argv[3]);
                    float inc = atof(argv[4]);
                    float roof = atof(argv[5]);
                    seqf(format,floor,inc,roof);
                    }
                    break;
            default:
                puts("Error");
        }

    }
    
    return 0;
}

void seqf(char* format, float floor, float inc, float roof){
    int size = strlen(format);
    char* preformat = strtok(format, "%"); // everything before '%'
     // everything after '%'*/
    int flag = 0;
    if((size - strlen(preformat)) >= 3)
         flag = 1;
    int space = 0;
    char* nf ;
    double i = floor;
    float a = floor;
    switch (format[size-1]){
        case 'g' : 
            nf = strtok(NULL, "g");
            if(flag){space = atoi(nf);}
            while(i<=roof){
                printf("%s",preformat);
                for(int a = 1; a<=space; a++){
                    printf(" ");
                }
                printf("%g",i);
                puts("");
                i+=inc;
            }
            break;
        case 'G' :
            nf = strtok(NULL, "G");
            if(flag){space = atoi(nf);}
            while(i<=roof){
                printf("%s",preformat);
                for(int a = 1; a<=space; a++){
                    printf(" ");
                }
                printf("%g",i);
                puts("");
                i+=inc;
            }
            break;
        case 'e' :
            nf = strtok(NULL, "e");
            if(flag){space = atoi(nf);}
            while(a<=roof){
               printf("%s",preformat);
                for(int i = 1; i<=space; i++){
                    printf(" ");
                }
                printf("%e",a);
                puts("");
                a+=inc;
            }
            break;

        case 'E' :
            nf = strtok(NULL, "E");
            if(flag){space = atoi(nf);}
            while(a<=roof){
                printf("%s",preformat);
                for(int i = 1; i<=space; i++){
                    printf(" ");
                }
                printf("%e",a);
                puts("");
                a+=inc;
            }
            break;

        case 'f' :
            nf = strtok(NULL, "f");
            if(flag){space = atoi(nf);}
            while(a<=roof){
                printf("%s",preformat);
                for(int i = 1; i<=space; i++){
                    printf(" ");
                }
                printf("%f",a);
                puts("");
                a+=inc;
            }
            break;

        default :
            exit(0);
            break;

    }

}
