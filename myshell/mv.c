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
#define SAME_INODE(a, b) ((a).st_ino == (b).st_ino && (a).st_dev == (b).st_dev)
int copy(char* a, char* b)
{ FILE *fptr1, *fptr2; 
    char filename[100], c; 
      
    fptr1 = fopen(a, "r"); 
    if (fptr1 == NULL) 
    { 
        printf("Cannot open file %s \n", a); 
        return 0;
    } 
  
    
    // Open another file for writing 
    fptr2 = fopen(b, "w"); 
    if (fptr2 == NULL) 
    { 
        printf("Cannot open file %s \n", b); 
        return 0;
    } 
  
    // Read contents from file 
    c = fgetc(fptr1); 
    while (c != EOF) 
    { 
        fputc(c, fptr2); 
        c = fgetc(fptr1); 
    } 
  
    printf("\nContents copied to %s", b); 
  
    fclose(fptr1); 
    fclose(fptr2); 
    return 1;

}
 
int move(char* a,char *b)
  { 
  struct stat statbuf_src, statbuf_dest;
  char *src, *dest, *new_src, *new_dest;
  
  src = malloc(strlen(a) + 1);
  dest = malloc(strlen(b) + 1);
  strcpy(src, a);
  strcpy(dest, b);

  stat(src, &statbuf_src);
  stat(dest, &statbuf_dest);
  
  
  
  // there are many more, of course
  printf("\"%s\" is a ", src);
  if (S_ISREG(statbuf_src.st_mode)) {
    puts("a regular file");
  }
  if (S_ISDIR(statbuf_src.st_mode)) {
    puts("a directory");
  }

  printf("\"%s\" is a ", dest);
  if (S_ISREG(statbuf_dest.st_mode)) {
    puts("a regular file");
  }
  if (S_ISDIR(statbuf_dest.st_mode)) {
    puts("a directory");
  }

  if (SAME_INODE(statbuf_dest, statbuf_src)) {
    printf("%s and %s are the identical\n", src, dest);
  }
  // if that is not set you have to do it by hand:
  // climb up the tree, concatenating names until the inodes are the same
  
   char current_directory[PATH_MAX];
  
   getcwd(current_directory, sizeof(current_directory)); 
   
   /*char *current_directory;
 
   current_directory = getenv("PWD");
  */
   printf("current directory is \"%s\"\n", current_directory);
  
  // I'm pretty sure it can be done in a much more elegant way
  new_src = malloc(strlen(src) + 1 + strlen(current_directory) + 1);
  strcpy(new_src,current_directory);
  strcat(new_src,"/");
  strcat(new_src,src);
 
  printf("new_src = %s\n",new_src);

  new_dest = malloc(strlen(dest) + 1 + strlen(current_directory) + 1 + strlen(src) + 1);
  strcpy(new_dest,current_directory);
  strcat(new_dest,"/");
  strcat(new_dest,dest);
  
  if(S_ISDIR(statbuf_dest.st_mode))
  { strcat(new_dest,"/");
    strcat(new_dest,src);
  }
  printf("new_dest = %s\n",new_dest);

  if(rename(new_src,new_dest) != 0){
    fprintf(stderr,"rename failed with error %s\n",strerror(errno));
  }

  free(new_src);
  free(new_dest);
  free(src);
  free(dest);

  return 0;
  }
  
  void help () 
{
	printf("Usage: mv [OPTION] [FILE/DIR] [FILE/DIR] \n Search for PATTERN in each FILE\n");
	printf("  -i          interactive move\n");
	printf("  -b          make backup of file with different name \n");
	printf("  -v          same as move but it print at the end command\n");
	printf("  -u          to update if source file is more recent then it will copy \n");
	printf("  -h  --help  for help \n");
	printf("Standard Input  : mv  [file/dir]   default DIR is [./] \n");
	printf("Standard Input with options : mv -i/-b/-v [file/dir]    default DIR is [./] \n");
}

int main(int argc,char** argv)
{ // current_directory = getenv("PWD");
   if(argc==2)
     { if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0 )
       { help();
         exit(0);
       }
     }
   if(argc<3){ printf("invalid option \n use --help or -h for help \n"); return 0;}
   
  if(argc==3)
   {
    move(argv[1],argv[2]);
   }
  if(argc==4)
   {
     if(strcmp(argv[1],"-u")==0)
         {
            struct stat s_src, s_dest;
       char *src, *dest, *new_src, *new_dest;
  
       src = malloc(strlen(argv[1]) + 1);
       dest = malloc(strlen(argv[2]) + 1);
       strcpy(src, argv[3]);
       strcpy(dest, argv[2]);
       if(stat(dest,&s_dest)==-1){ printf("wrong file name \n"); exit(0);}
       if(stat(src,&s_src)==-1){ printf("wrong file name \n"); exit(0);}
       
       time_t dest_st_time=s_dest.st_mtime;
       time_t src_st_time=s_dest.st_mtime;
       
       //printf("%ld  %ld ",src_st_time,dest_st_time);
       
       if(src_st_time > dest_st_time)
            {
             move(argv[2],argv[3]);
             printf("YES");
            }
       
      
      
       exit(0);
      }
     if(strcmp(argv[1],"-b")==0)
         {
          /*string s,new;
          strcpy(s,"old_");
          strcat(s,argv[3]);
          strcpy(new,"tamp");
         */
           
           copy(argv[3],"xyz"); 
           
           if(rename("xyz","old-file") != 0)
           {
            fprintf(stderr,"rename failed with error %s\n",strerror(errno));
           }
           
           move(argv[2],argv[3]);
         }
   
   if(strcmp(argv[1],"-i")==0)
        {
          char ch;
          printf("Do want to move %s to %s Y/n ?? ",argv[2],argv[3]);
          scanf("%c",&ch);
          if(ch=='Y')
            {
              move(argv[2],argv[3]);
            }
          
          
        }
    if(strcmp(argv[1],"-v")==0)
        {
          char ch;
            if(move(argv[2],argv[3]))
              printf(" renamed  '%s' --> '%s'  ",argv[2],argv[3]);
              
          
        }    
   
   }
    printf("invalid option \n use --help or -h for help \n");


return 0;
}

