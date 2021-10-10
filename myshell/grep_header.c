

#include "grep_header.h"

char * mystrstr (char *a, char *b) 
  {
	char *p = a, *q = b,*z=NULL;
	while(*p != '\0' && *q != '\0') {
		if(*p == *q)  {
			p++;
			q++;
		}
		else { 
			if(q == b)
				p++;
			else  {
				p = p - (q- b) + 1;
				q = b;
			}
		}
	}
	if(*q == '\0')
		return p - strlen(b);
	else 
		return z;
}

char * mystrstrcase (char *a, char *b) {
	char *p = a, *q = b,*z=NULL;
	while(*p != '\0' && *q != '\0') {
		if((*p == *q) || ((*p - 'a' + 'A') == *q) || ((*p + 'a' - 'A') == *q)) {
			p++;
			q++;
		}
		else { 
			if(q == b)
				p++;
			else  {
				p = p - (q - b) + 1;
				q = b;
			}
		}
	}
	if(*q == '\0')
		return a;
	else 
		return z;
}
char *mystrtok_multi(char *a, char *de, int x) {
	static char *c;
	static int j[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	static int i[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int p = 0;
	if(a != NULL) {
		c = a;
		while(c[i[x]] != '\0') {
			if(c[i[x]] == de[0])
				c[i[x]] = '\0';
			i[x]++;
		}
		while(c[j[x]] == '\0')
			j[x]++;
		return &c[j[x]];
	}
	else {
		while(j[x] < (i[x]-1))  {
			if(c[j[x]] == '\0' && c[j[x]]+1 != '\0') { 
				j[x]++; 
				return &c[j[x]];
			}
			j[x]++;
		}
		c = NULL;
		return NULL;
	}
}        	

void recursive(char *dname, char *search, int FLAG) {
	int f[6], size[6], i = 0;
	char *a;	
	char s[2] = "\n";
   	char *token;
		DIR *dir;
   		dir=opendir(dname);
  		struct dirent *dent;
  		if(dir!=NULL) {
       			while((dent = readdir(dir))) {
				if(dent->d_type == DT_DIR) {
					if(strcmp(dent->d_name, ".") == 0 || strcmp(dent->d_name, "..") == 0); 
					else  {
                                        	strcat(dname, "/");
                                                strcat(dname, dent->d_name);
						if(FLAG == 0)
                                                	recursive(dname, search, 0);
						else if(FLAG == 1)
                                                	recursive(dname, search, 1);
						else if(FLAG == 2)
                                                	recursive(dname, search, 2);
                                        }
				}
				else if(f[i] = open(dent->d_name, O_RDONLY)) { 
					size[i] = lseek(f[i], 0, SEEK_END);
					a = (char*)malloc(size[i]*sizeof(char));
					lseek(f[i], 0, 0);	
					read(f[i], a, size[i]*sizeof(char));
   					token = strtok(a, s);
 					while( token != NULL ) { 
			      if((mystrstr( token, search) != NULL && FLAG == 0) || (mystrstrcase(token, search) != NULL && FLAG == 1) || (mystrstr(token, search) == NULL && FLAG == 2)) {
							printf("%s%s/%s%s:%s%s\n", KMAG, dname, dent->d_name, KBLU, KNRM, token);
						}
						token = strtok(NULL, s);
   					}
				close(f[i]);
				free (a);
				}
			i++;
			}
           		closedir(dir);
		}	
}

void standard_input(char *b) {
	char c;
	char *a; 
        int i = 0;
        a = (char*)malloc(128*sizeof(char));
        while(scanf("%c", &c) != -1) {
     		if(c == '\n') {
			a[i] = '\0';
	                if(mystrstr(a, b) != NULL)
                        	printf("%s\n", a);
                        free(a);
                        a = (char*)malloc(128*sizeof(char));
                        i = 0;
                }
                else
                        a[i++] = c;
	}
}
void standard_options(char *option, char *b) {
        char c;
        char *a;
        int i = 0;
        a = (char*)malloc(128*sizeof(char));
        while(scanf("%c", &c) != -1) {
                if(c == '\n') {
                        a[i] = '\0';
			if(strcmp(option, "-i") == 0) {
                        	if(mystrstrcase(a, b) != NULL)
                                	printf("%s\n", a);
			}
			else if(strcmp(option, "-v") == 0) {
                        	if(mystrstr(a, b) == NULL)
                                	printf("%s\n", a);
			}
			else if(strcmp(option, "-iv") == 0 || strcmp(option, "-vi") == 0)
                        	if(mystrstrcase(a, b) == NULL)
                                	printf("%s\n", a);
                        free(a);
                        a = (char*)malloc(128*sizeof(char));
                        i = 0;
                }
                else
                        a[i++] = c;
        }
}
void help () {
	printf("Usage: grep [OPTION] PATTERN [FILE]...\n Search for PATTERN in each FILE\n");
	printf("  -w       force PATTERN to match only whole words\n");
	printf("  -i       ignore case distinctions\n");
	printf("  -in      ignore case distinctions and print with line\n");
	printf("  -vc      count case distinctions which not match\n");
	printf("  -n       print line number with output lines\n");
	printf("  -c       print only a count of matching lines per FILE\n");
	printf("Standard Input :ls PATTERN\n");
	printf("Standard Input with options : ./grep -i/-v/-iv PATTERN\n");
}

