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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void help ()
 {
	printf(" Following command are serviceable \n\n");
	printf("  ls      listing files and directory \n");
	printf("             for more information about ls type ' ls --help '\n \n");
        printf("  grep    finding pattern in file \n");
        printf("             for more information about grep type ' grep --help '\n \n");
	printf("  cp      copy file from one place to another\n");
	printf("             for more information about cp type ' cp --help '\n \n");
	printf("  mv      move file from one place to another\n");
	printf("             for more information about mv type ' mv --help '\n \n");
	printf("  ps      see details status about proceses\n");
	printf("             for more information about ps type ' ps --help '\n \n");
	printf("  EXIT/Exit/exit    terminate myshell\n\n");
	printf("--help /-h :for more information\n\n");
	//printf("  for further details about myshell . read read_me.txt file or type DETAILS command \n\n");
  }

void handler(int sig){
 kill(getpid(),SIGINT);
return;
}
int main() {
    
    signal(SIGUSR2, handler);
    
        printf("|-----------------------------------------------------------------------------|\n");
	printf("|                                                       date :04-01-2021      |\n");
	printf("|             COMPUTER SYSTEM                                                 |\n");
	printf("|                                                                             |\n");
	printf("|       NAME     : PATEL MIT KUMAR RAJESHBHAI                                 |\n");
	printf("|       ENTRY_NO : 2020CSM1016                                                |\n");
	printf("|-----------------------------------------------------------------------------|\n");

    char* line, prompt[100];
    pid_t child_pid;
    int stat_loc;
    char hostname[HOST_NAME_MAX];
    char username[LOGIN_NAME_MAX];
    gethostname(hostname, HOST_NAME_MAX);
    getlogin_r(username, LOGIN_NAME_MAX);
    char cwd[PATH_MAX];
  
    getcwd(cwd, sizeof(cwd));  
    int c=0,i=0;while(c < 3 && i<strlen(cwd)){ if(cwd[i]=='/') {c++;} i++;}
    char* dir=cwd+i-1;
    dir[0]='/';
   
    while (1)
     { 
        snprintf(prompt, sizeof(prompt), ANSI_COLOR_GREEN "%s@%s" ANSI_COLOR_RESET ":"ANSI_COLOR_BLUE"~%s"ANSI_COLOR_RESET"$ " ,username,hostname,dir );
        line = readline(prompt);
        if (!line)
            break;
        add_history(line);
        

        child_pid = fork();
        
        if (child_pid == 0)
         {  char* line1;
            //scanf("%[^\n]*\n",line);
           
                
            char *token,*argv[20],*cmd;
            token=strtok(line," ");
            cmd=token;
            if(strcmp(cmd,"--help")==0 || strcmp(cmd,"-h")==0 || strcmp(cmd,"help")==0)
             { help(); exit(0); }
            if(strcmp(cmd,"exit")==0 || strcmp(cmd,"Exit")==0 || strcmp(cmd,"EXIT")==0)
            { kill(getppid(), SIGUSR2);
              exit(0);
            }
            
            argv[0]=cmd;
            int i=1;
            while(token!=NULL)
            {
              token=argv[i]=strtok(NULL," ");
              i++;
            }
            /* Never returns if the call is successful */
            if(execve(cmd,argv,NULL)==-1)
            {  printf("wrong command");
            }
            printf("\ncommand is invalid use --help to usage\n");
            exit(0);
         }
         else 
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }
       free(line);
     }

    return 0;
}

