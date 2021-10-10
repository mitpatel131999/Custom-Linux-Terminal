

/*
 *  COMPUTER SYSTEM
 *
 *  PROJECT
 *
 *  NAME     : PATEL MIT KUMAR
 *
 *  ENTRY NO :2020CSM1016
 *
 *  PROBLEM  :2
 */
 
 use help.txt for more information
 
 To compile all program at same time there is compile.c file 
    
        for compile.c   :$ gcc -o terminal compile.c
                 run    :$ ./terminal
                 
                 
 second way is compile all file one by one
  
        for      ls.c   :$ gcc -o ls ls.c
                
        for      ps.c   :$ gcc -o ps ps.c
                
        for      cp.c   :$ gcc -o cp cp.c
                
        for      mv.c   :$ gcc -o mv mv.c
                
        for    grep.c   :$ gcc -o grep grep_header.c grep.c
                
        for myshell.c   :$ gcc myshell.c -L/usr/include -lreadline -o myshell
                
                 run    :$ ./myshell


 
