


#ifndef __GREP_HEADER_H__
#define __GREP_HEADER_H__




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
/*//#include "header.h"*/
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"





void recursive(char *, char *, int);
char *mystrstr (char *, char *);
char *mystrstrcase (char *, char *);
char *mystrtok_multi (char *, char *, int);
void standard_options(char *, char *);
void standard_input(char *);
void help();
/*
//void _w_(int argc,char** argv);
//void _i_(int argc,char** argv);
//void _A_(int argc,char** argv);
//void _r_(int argc,char** argv);
//void _c_(int argc,char** argv);

*/
#endif /* __HEADER_H__ */
/* $end header.h */
