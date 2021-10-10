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

 #define MAX_SIZE 2
 #define MAX_BUF_SIZE 256
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
  
    printf("\nContents copied to %s\n", b); 
  
    fclose(fptr1); 
    fclose(fptr2); 
    return 1;

}

void help () 
{
	printf("Usage: cp [OPTION] [FILE] [FILE/DIR] \n Search for PATTERN in each FILE\n");
	printf("  -p          peserve permission access time modify time etc\n");
	printf("  -b          make backup of file with different name \n");
	printf("  -f          use to copy fource fully\n");
	printf("  -u          to update if source file is more recent then it will copy \n");
	printf("  -h  --help  for help \n");
	printf("Standard Input  : cp  [file]   default DIR is [./] \n");
        printf("Standard Input with options : cp -p/-b/-f [file] default DIR is [./] \n");
}

 int main(int argc, char** argv)
 { 
    if(argc==2)
     { if(strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0 )
       { help();
         exit(0);
       }
     }
   if(argc<3){ printf("invalid option \n use --help or -h for help \n"); return 0;}
   if(argc==3)
     {
      copy(argv[1],argv[2]);
      exit(0);
     }
   if(argc==4)
    { 
     if(strcmp(argv[1],"-p")==0)
      { 
       struct stat statbuf_src, s_dest;
       char *src, *dest, *new_src, *new_dest;
       char *current_directory;
  
       src = malloc(strlen(argv[1]) + 1);
       dest = malloc(strlen(argv[2]) + 1);
       strcpy(src, argv[1]);
       strcpy(dest, argv[2]);
       //tamp=(struct stat *)malloc(sizeof(struct stat));
       //s_dest2=(struct stat*)malloc(sizeof(struct stat));
       if(stat(dest,&s_dest)==-1){ printf("wrong file name \n"); exit(0);}
       if(stat(src,&statbuf_src)==-1){ printf("wrong file name \n"); exit(0);}
       mode_t tamp_st_mode=s_dest.st_mode;
       uid_t tamp_st_uid=s_dest.st_uid;
       gid_t tamp_st_gid=s_dest.st_gid;
       time_t tamp_st_atime=s_dest.st_atime;
       time_t tamp_st_mtime=s_dest.st_mtime;
       printf("%d \n",statbuf_src.st_mode);    
       
       printf("%d \n",tamp_st_mode);    
        copy(argv[2],argv[3]); 
       
       stat(dest,&s_dest);   
       s_dest.st_mode=tamp_st_mode;
       s_dest.st_uid=tamp_st_uid;
       s_dest.st_gid=tamp_st_gid;
       s_dest.st_atime=tamp_st_atime;
       s_dest.st_mtime=tamp_st_mtime;
       
       printf("%d \n",s_dest.st_mode);    
       exit(0);
       }
       
   
    if(strcmp(argv[1],"-b")==0)
       { char* s;
         char* new;
        /* strcpy(s,"old_");
         strcat(s,argv[3]);
         strcpy(new,"tamp");
         */
          //strcpy(s,"old_");
          if(rename(argv[3],s) != 0){
           fprintf(stderr,"rename failed with error %s\n ",strerror(errno));
           }
           char sop;
           scanf("%c",&sop);
           
         copy(argv[2],new); 
         
        
         if(rename(new,argv[3]) != 0){
           fprintf(stderr,"rename failed with error %s\n",strerror(errno));
           }
         
        exit(0);
       }
       
    if(strcmp(argv[1],"-f")==0)
       {
       struct stat statbuf_src, s_dest;
       char *src, *dest, *new_src, *new_dest;
  
       src = malloc(strlen(argv[1]) + 1);
       dest = malloc(strlen(argv[2]) + 1);
       strcpy(src, argv[3]);
       strcpy(dest, argv[2]);
        if(stat(dest,&s_dest)==-1){ printf("wrong file name \n"); exit(0);}
       
       mode_t tamp_st_mode=s_dest.st_mode;
         printf("%d \n",tamp_st_mode);    
       
        char mode[] = "0777";
        int i;
        i = strtol(mode, 0, 8);
        if (chmod (argv[2],i) < 0)
        {
          //fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
           //     argv[0], , mode, errno, strerror(errno));
          exit(1);
        }
        stat(dest, &s_dest);
        printf("%d \n",s_dest.st_mode);    
       
        copy(argv[2],argv[3]);
        stat(dest, &s_dest);
       
        s_dest.st_mode=tamp_st_mode;
        printf("%d \n",s_dest.st_mode);    
        exit(0);
       }
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
             copy(argv[2],argv[3]);
             //printf("YES");
            }
       
      
      
       exit(0);
      }  
         
    }
  
  printf("invalid option  \n use --help or -h for help \n");  
return 0;
}
