#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <limits.h>


int main()
{
 system("gcc myshell.c -L/usr/include -lreadline -o myshell");
 system("gcc -o grep grep_header.c grep.c");
 system("gcc -o cp cp.c");
 system("gcc -o mv mv.c");
 system("gcc -o ls ls.c");
 system("gcc -o ps ps.c");
 
 system("clear");
 system("./myshell");
 
 return 0;
}
