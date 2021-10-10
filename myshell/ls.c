#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include<string.h>
#include<time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

struct fileInfo {
	char name[20];
	char time[25];
	int size;
	struct stat mystat;
};

#include <pwd.h>
#include <grp.h>
char* getUser(uid_t uid)
{
    struct passwd *pws;
    pws= getpwuid(uid);
        return pws->pw_name;
}



struct fileInfo file[100];
    
double sizeSortAscending(const void *p1, const void *p2) {

	struct fileInfo * ptr1 = (struct fileInfo *) p1;
	struct fileInfo * ptr2 = (struct fileInfo *) p2;

	//return difference
	return (double)((ptr1->size) - (ptr2->size));
}

int nameSortDescending(const void *p1, const void *p2) {
	struct fileInfo * ptr1 = (struct fileInfo *) p1;
	struct fileInfo * ptr2 = (struct fileInfo *) p2;

	//returing strcmp  val
	return strcmp(ptr2->name, ptr1->name);
}


int sort_size(int n)
  {
     for(int i=0;i<n;i++)
        {
          for(int j=i+1;j<n;j++)
          { if(sizeSortAscending( &file[i],&file[j] ) < 0 )
             {
              struct fileInfo * ti;
              *ti=file[i];
              file[i]=file[j];
              file[j]=*ti;
             
             }          
          }
        }
  }


int sort_ls(int n)
       {
       
       for(int i=0;i<n;i++)
        {
          for(int j=i+1;j<n;j++)
          {
            if(nameSortDescending( &file[i],&file[j] ) < 0 )
             {struct fileInfo * t;
              *t=file[i];
              file[i]=file[j];
              file[j]=*t;
             
             }          
          }
        }
       
       
       
      return 0; 
       }

void help () 
{
	printf("Usage: ls [OPTION] [FILE]...\n Search for PATTERN in each FILE\n");
	printf("  -l          fot listing permission ,uid etc\n");
	printf("  -lS         fot listing permission ,uid etc shorted by size\n");
	printf("  -o          same as -l but do not print group \n");
	printf("  -oS         same as -l but do not print group \n");
	printf("  -s          print size and name in order\n");
	printf("  -sS         print size and name in order\n");
	printf("  -S          print size in order with name \n");
	printf("  -i          print inode with file name \n");
	printf("  -iS         print inode with file name \n");
	printf("  -h  --help  for help \n");
	printf("Standard Input  : ls [./] \n");
	printf("Standard Input with options : ls -i/-v/-iv [./]\n");
}



int main(int argc, char* argv[])
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    int total=0;
    time_t curtime;
    
    if(argc==2)
     { if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0 )
       { help();
         exit(0);
       }
     }
  /*  if(argc<2){ argc=3; strcpy(argv[1],"default");strcpy(argv[2],"./");} 
    else if(argc==2)
         {  argc=3;
            if(strcmp(argv[1],"-l")==0 || strcmp(argv[1],"-o")==0 || strcmp(argv[1],"-i")==0 || strcmp(argv[1],"-s")==0 || strcmp(argv[1],"-S")==0 )
              {
               strcpy(argv[2],"./");
              }
             else
              {
              strcpy(argv[2],argv[1]);
              strcpy(argv[1],"default");
              } 
         }
       else
       {
        }
        */
    int cou=0;    
    if( argc<2){ cou++; }    
    if( argc<3){ mydir = opendir("./"); }
    else{ mydir = opendir(argv[2]); }   
    int i=0;
    argc=3;
    i=0; 
    while((myfile = readdir(mydir)) != NULL)
    {
        strcpy(file[i].name,myfile->d_name);  
        stat(myfile->d_name, &file[i].mystat);
        strcpy(file[i].time,ctime(&(file[i].mystat.st_atime)));
        file[i].size=file[i].mystat.st_size;
        file[i].time[24]=' ';
        total=total+file[i].mystat.st_blocks;
        i++;
         
    }
    
    int n=i;
   if(argc==3) 
   { if( cou >0  || strcmp(argv[1],"default")==0 )
       {
         sort_ls(n);
         for(int i=0;i<n;i++)
         {
           if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
           if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
            //if ((mystat.st_mode & S_IRUSR))
            //    printf(ANSI_COLOR_RED);     
             printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
         }
         exit(0);
       }
     if(strcmp(argv[1],"-l")==0 || strcmp(argv[1],"-ls")==0 || strcmp(argv[1],"-sl")==0)
       {printf("total size is %d \n",total);
        sort_ls(n);
         time_t c;
        for(int i=0;i<n;i++)
        {  
         // printf("\n %40s %10d ",file[i].name,file[i].mystat.st_size);
           
        int x=file[i].mystat.st_mode;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        printf("-  ");
        printf("%4.1ld  ",file[i].mystat.st_nlink);
        
        
        struct group *grp;
        struct passwd *pwd;

        grp = getgrgid(file[i].mystat.st_gid);
        pwd = getpwuid(file[i].mystat.st_uid);
        printf(" %8s ", pwd->pw_name);
        printf(" %8s ", grp->gr_name);
        printf("  %8ld  ",file[i].mystat.st_size);
        
        printf("%25s",file[i].time);
         
        if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
            
         } 
          exit(0);  
      }
     if(strcmp(argv[1],"-o")==0 || strcmp(argv[1],"-os")==0||strcmp(argv[1],"-so")==0)
      {  printf("total size is %d \n",total);
         sort_ls(n);
         time_t c;
        for(int i=0;i<n;i++)
        {  
         // printf("\n %40s %10d ",file[i].name,file[i].mystat.st_size);
           
        int x=file[i].mystat.st_mode;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        //x=x/8;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        printf("-  ");
        printf("%3.1ld",file[i].mystat.st_nlink);
        printf(" %8s",getUser(file[i].mystat.st_uid));
        printf(" %8.1ld ",file[i].mystat.st_size);
        
        printf("%25s",file[i].time);
         
        if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
            
         } 
          exit(0);  
       }
 
     if(strcmp(argv[1],"-i")==0)
      { sort_ls(n);
        for(int i=0;i<n;i++)
        {
         printf("%10ld ",file[i].mystat.st_ino);
         if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
        }
         exit(0);
      }
      if(strcmp(argv[1],"-iS")==0 || strcmp(argv[1],"-Si")==0)
      { sort_ls(n);
        for(int i=0;i<n;i++)
        {
         printf("%10ld ",file[i].mystat.st_ino);
         if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
        }
         exit(0);
      }
     if(strcmp(argv[1],"-s")==0)
      {  sort_ls(n);
         printf(ANSI_COLOR_RED);
         printf("total size is "ANSI_COLOR_MAGENTA"%d \n",total);
         printf(ANSI_COLOR_RESET); 
        
        for(int i=0;i<n;i++)
        {
        printf("%10ld ",file[i].mystat.st_size);
         if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
        }
        exit(0);
      }
      if(strcmp(argv[1],"-sS")==0 || strcmp(argv[1],"-Ss")==0)
      {  sort_size(n);
         printf(ANSI_COLOR_RED);
         printf("total size is "ANSI_COLOR_MAGENTA"%d \n",total);
         printf(ANSI_COLOR_RESET); 
        
        for(int i=0;i<n;i++)
        {
        printf("%10ld ",file[i].mystat.st_size);
         if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
        }
        exit(0);
      }
     if(strcmp(argv[1],"-S")==0)
      { printf(ANSI_COLOR_RED);
        //printf("total size is "ANSI_COLOR_MAGENTA"%d \n",total);
        printf(ANSI_COLOR_RESET); 
        sort_size(n);
        for(int i=0;i<n;i++)
        {
        //printf("%10ld ",file[i].mystat.st_size);
         if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
        
        }
        exit(0);
      }
      if(strcmp(argv[1],"-lS")==0 || strcmp(argv[1],"-Sl")==0 || strcmp(argv[1],"-sSl")==0||strcmp(argv[1],"-Ssl")==0||strcmp(argv[1],"-Sls")==0 ||strcmp(argv[1],"-slS")==0||
        strcmp(argv[1],"-lsS")==0||strcmp(argv[1],"-lSs")==0)
       {printf("total size is %d \n",total);
        sort_size(n);
         time_t c;
        for(int i=0;i<n;i++)
        {  
         // printf("\n %40s %10d ",file[i].name,file[i].mystat.st_size);
           
        int x=file[i].mystat.st_mode;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        printf("-  ");
        printf("%4.1ld  ",file[i].mystat.st_nlink);
        
        
        struct group *grp;
        struct passwd *pwd;

        grp = getgrgid(file[i].mystat.st_gid);
        pwd = getpwuid(file[i].mystat.st_uid);
        printf(" %8s ", pwd->pw_name);
        printf(" %8s ", grp->gr_name);
        printf("  %8ld  ",file[i].mystat.st_size);
        
        printf("%25s",file[i].time);
         
        if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
            
         } 
          exit(0);  
      }
      if(strcmp(argv[1],"-oS")==0 || strcmp(argv[1],"-So")==0 || strcmp(argv[1],"-sSo")==0 || strcmp(argv[1],"-Sso")==0 || strcmp(argv[1],"-Sos")==0 || strcmp(argv[1],"-soS")==0 || 
       strcmp(argv[1],"-osS")==0 || strcmp(argv[1],"-oSs")==0)
      {  printf("total size is %d \n",total);
         sort_size(n);
         time_t c;
         for(int i=0;i<n;i++)
         {  
         // printf("\n %40s %10d ",file[i].name,file[i].mystat.st_size);
           
        int x=file[i].mystat.st_mode;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        //x=x/8;
        printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        x=x/8;
        //printf("-");
        if(x%8==0){ printf("---"); }
        if(x%8==1){ printf("--x"); }
        if(x%8==2){ printf("-w-"); }
        if(x%8==3){ printf("-wx"); }
        if(x%8==4){ printf("r--"); }
        if(x%8==5){ printf("r-x"); }
        if(x%8==6){ printf("rw-"); }
        if(x%8==7){ printf("rwx"); }
        printf("-  ");
        printf("%3.1ld",file[i].mystat.st_nlink);
        printf(" %8s",getUser(file[i].mystat.st_uid));
        printf(" %8.1ld ",file[i].mystat.st_size);
        
        printf("%25s",file[i].time);
         
        if(S_ISDIR(file[i].mystat.st_mode))
             printf(ANSI_COLOR_BLUE);
        if (S_ISREG(file[i].mystat.st_mode))
             printf(ANSI_COLOR_GREEN);
        //if ((mystat.st_mode & S_IRUSR))
         //    printf(ANSI_COLOR_RED);     
            printf(" %s\n",file[i].name);
             printf(ANSI_COLOR_RESET); 
            
         } 
          exit(0);  
       }
    }    
    printf("invalid  option, use --help command for usage \n");
    
    exit(0);
    closedir(mydir);
   return 0;
}
