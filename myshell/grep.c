#include <stdio.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h> 
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>     
#include "grep_header.h"
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
void _c_(int argc,char** argv)
{       int f[10], size[10], i = 0;
	char *a;	
	char s[2] = "\n";
   	char *token;
	 
               if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-cv") == 0 || strcmp(argv[1], "-vc") == 0) {
		int count[10];
		for(i = 0; i < 10; i++)
			count[i] = 0;
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				if(strcmp(argv[1], "-c") == 0) {
					if(mystrstr( token, argv[2]) != NULL) {
						count[i-1]++;
					}
				}
				else {
					if(mystrstr( token, argv[2]) == NULL) {
						count[i-1]++;
					}
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			if(f[i] != -1) {
				if(argc < 5)
					printf("%d\n", count[i-1]);
				else
					printf("%s%s %s: %s%d\n", KMAG, argv[i+2], KBLU, KNRM, count[i-1]);
			}
			close(f[i]);
			free (a);
		}
		return 0;
	}
 }
 void _i_(int argc,char** argv)
 {         int f[10], size[10], i = 0;
	char *a;	
	char s[2] = "\n";
   	char *token;
	
               if(strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-in") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstrcase( token, argv[2]) != NULL) {
					if(strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-ni") == 0) {
						if(argc < 5)
							printf("%s%d%s:%s%s\n", KGRN, line_num, KBLU, KNRM, token);
						else
							printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, line_num, KBLU, KNRM, token);
					}
					else {
						if(argc < 5)
							printf("%s\n", token);
						else
							printf("%s%s %s: %s%s\n", KMAG, argv[i+2], KBLU, KNRM, token);
					}
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
	}
void _w_(int argc,char** argv){
           
        int f[10], size[10], i = 0;
	char *a;	
	char s[2] = "\n";
   	char *token;
	
           if(strcmp(argv[1], "-w") == 0) {
                char *p;
                for(i = 1; i <= 10; i++) {
                        f[i] = open(argv[i+2], O_RDONLY);
                        size[i] = lseek(f[i], 0, SEEK_END);
                }
                for(i = 1; i <= 10; i++) {
                        a = (char*)malloc(size[i]*sizeof(char));
                        lseek(f[i], 0, 0);
                        read(f[i], a, size[i]*sizeof(char));
                        token = mystrtok_multi(a, s, i);
                        while( token != NULL ) {
                                if(p = mystrstr(token, argv[2])) {
                                        if(isalpha(*(p - 1)) == 0 && isalpha(*(p + strlen(argv[2]))) == 0) {
                                                if(argc < 5)
                                                        printf("%s\n", token);
                                                else
                                                        printf("%s%s : %s%s\n", KMAG, argv[i+2], KNRM, token);
                                        }
                                }
                                token = mystrtok_multi(NULL, s, i);
                        }
                        close(f[i]);
                        free (a);
                }
                return 0;

         }
        } 
 void _n_(int argc,char** argv)
  {  
     int f[10], size[10], i = 0;
     char *a;	
     char s[2] = "\n";
     char *token;
	  
     if(strcmp(argv[1], "-n") == 0) {
		for(i = 1; i <= 10; i++) {
			f[i] = open(argv[i+2], O_RDONLY);
			size[i] = lseek(f[i], 0, SEEK_END);
		}
		for(i = 1; i <= 10; i++) {
			int line_num = 0;
			a = (char*)malloc(size[i]*sizeof(char));
			lseek(f[i], 0, 0);	
			read(f[i], a, size[i]*sizeof(char));
   			token = mystrtok_multi(a, s, i);
 			while( token != NULL ) { 
				line_num++;
				if(mystrstr( token, argv[2]) != NULL) {
					if(argc < 5)
						printf("%s%d%s:%s%s\n", KGRN, line_num, KBLU, KNRM, token);
					else
						printf("%s%s %s: %s%d %s: %s%s\n", KMAG, argv[i+2], KBLU, KGRN, line_num, KBLU, KNRM, token);
				}
				token = mystrtok_multi(NULL, s, i);
  	 		}
			close(f[i]);
			free (a);
		}
		return 0;
	}
  }    
     
int main(int argc, char *argv[]) {
        //for(int i=0;i<argc;i++){ printf(" |%s| ",argv[i]); }
        
        if(argc == 1) {
		printf("Use grep -h command for help\n");
		exit(1);
	}
	else if((strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0 ) && argv[2] == NULL) {
		help();
		exit(1);
	}
	if(argc < 3 && strcmp(argv[0], "grep") != 0) {
		errno = EINVAL;
		perror("Bad arguments");
		return errno; 
	}
	else if(argc < 3 || (argc < 4 && argv[1][0] == '-')) {
		if(argc < 3)
			standard_input(argv[1]);
		if(argc < 4)
			standard_options(argv[1], argv[2]);
		exit(1);
	}
	else
	{
          if(strcmp(argv[1],"-i") == 0 || strcmp(argv[1],"-in") == 0 || strcmp(argv[1],"-in") == 0){_i_(argc,argv);exit(0);}
          if(strcmp(argv[1],"-c") == 0 || strcmp(argv[1],"-cv") == 0 || strcmp(argv[1],"-vc") ==0){_c_(argc,argv);exit(0);}
          if(strcmp(argv[1], "-w") == 0){_w_(argc,argv);exit(0);}
          if(strcmp(argv[1], "-n") == 0){_n_(argc,argv);exit(0);}
        }
        printf("invalid option \n use --help for usage \n");
      // if(strcpy(argv[1],"--help")==0 || strcpy(argv[1],"-")==0 )
       { //help();
       }




return 0;
}
