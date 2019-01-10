#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include </usr/include/wait.h>
#include <signal.h>
int pfds[2];
int count=0;
char input={'\0'};
char *pathv[100];
char commandLine[100];
char result[300]={'\0'};
char filename[25];
void sigint_handler(int sig){
	return;
}
void sigkill_handler(int sig){
	return;
}
int readinput(char * buf, char * input)
{
    count = 0;
    while((*input != '\n') && (count < 100)) {
        buf[count++] = *input;
        *input = getchar();
    }
    buf[count] = '\0';
    return 0;
}

char * findPath(char **argv, char **dir) {
  
    char pName[100];
    if( *argv[0] == '/'){
        return argv[0];
    }
    else if( *argv[0] == '.') {
        if( *++argv[0] == '.') {
                sprintf(result,"%s%s%s",pName,"/",argv[0]);
            return result;
        }
        //*--argv[0];
        if( *++argv[0] == '/') {
            if(getcwd(pName,sizeof(pName)) == NULL)
                perror("getcwd(): error\n");
            else {
                sprintf(result,"%s%s",pName,argv[0]);
            }
            return result;
        }
    }
    // look in PAH directories, use access() to see if the
    // file is in the dir
    int i;
    for(i = 0 ; i < 100 ; i++ ) {
        if(dir[i] != NULL) {
            sprintf(result,"%s%s%s",  dir[i],"/",argv[0]);
            if(access(result, X_OK) == 0) {
                return result;
            }
        }
        else continue;
    }
    
    fprintf(stderr, "%s: command not found\n", argv[0]);
    return NULL;
}

int parsePath(char* dirs[]){
    char* pathEnvVar;
    char* thePath;
    char* buff;
    char* path =getcwd(buff,100);
    int i;
    
    for(i=0 ; i < 100 ; i++ )
        dirs[i] = NULL;
    pathEnvVar = (char*) getenv("PATH");
    thePath = (char*) malloc(strlen(pathEnvVar) +strlen(path)+2);
    strcpy(thePath, pathEnvVar);
    strcat(thePath,":");
    strcat(thePath,path);
    char* pch;
    pch = strtok(thePath, ":");
    int j=0;
    // loop through the thePath for ':' delimiter between each path name
    while(pch != NULL) {
        pch = strtok(NULL, ":");
        dirs[j] = pch;
        j++;
    }
    return 0;
}
void foreground(char * pch,char **argv,int argc,char* pathv[100],int flag){
	int i=0;
	while (pch != NULL) {
		argv[i] = pch;
		pch = strtok (NULL, " ");
		i++;
	}
	argc = i;
	argv[i++] = NULL;
	char * name = findPath(argv, pathv);
	if(name == NULL) {
		printf("error \n");
	}
	int status;
	pid_t pid;
	pid=fork();
	if(pid==0) {

		if(flag==1){
			int fd=open(filename,O_WRONLY|O_CREAT,0600);
			dup2(fd,1);
			close(fd);	
		}
		if(flag == 4){
			int fd=open(filename,O_RDONLY,0600);
			dup2(fd,0);
			close(fd);
		}
		if(flag==3)
			printf("Process %d running in background mode \n",getpid());

		if(execv(name, argv)==-1){
		printf("Child process failed \n");}
		

	}
	else if(pid > 0) {
		signal(SIGINT,sigint_handler);
		if(flag ==3){
		signal(SIGKILL,sigkill_handler);
		}
		if(flag!=3){
			waitpid(pid, &status, 0);
		}
	}
}
int main(int argc, char* argv[])
{
	int pid;
	parsePath(pathv);
	while(1) {
	printf("minish> ");
        input =getchar();
        if(input == '\n')
     	 {
            continue;
        }
        else {
		int flag=0;
            readinput(commandLine,&input);
            if((strcmp(commandLine, "exit") == 0)){
             	kill(pid,SIGKILL);
		 break;
	    }
	    int j=0;
	    while(commandLine[j]!='\0'){
		    if(commandLine[j] == '&'){
			    commandLine[j]='\0';
			    flag=3;
			    break;
		    }
		    else if(commandLine[j]=='>'){
			    flag=1;
			    break;
		    }
		    else if(commandLine[j]=='<'){
				flag=4;
				break;
		    }
	    	j++;
	    }
	    if(flag ==4 || flag == 1){
		    int v=0,k=0;
		    while(commandLine[j]!='\0'){
			    if(v==1){
				filename[k++]=commandLine[j];
			    	filename[k]='\0';	
			    	commandLine[j]='\0';
			    }
			    if((commandLine[j] == '<')||(commandLine[j] == '>')){
				    v=1;
				    commandLine[j]='\0';
			    }
			    j++;
		    }
	    }
            char * pch;
            pch = strtok (commandLine," ");
	    foreground(pch,argv,argc,pathv,flag);
	}
    }

    		printf("\n");
		return 0;
    
}
