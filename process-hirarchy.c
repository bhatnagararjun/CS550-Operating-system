#include<stdio.h>	//imported for printf
#include<stdlib.h>      //imported for atoi and sprinf
#include<unistd.h>	//imported for fork and exec
#include</usr/include/wait.h> //imported for wait

int i=0;
void create_child(int H,int C,char *argv){
	
	int wstatus;
	if(H>1){
	
		pid_t pid;
		if(C>0){	//check it C is not 0 or -tive
		pid=fork();	//create a new process	
	
		}
	
		else{
	
			printf("wrong input");
			exit(-1);
	
		}
	
		if(pid == 0){ 				//we are in the child process
	
			i=0;
			int h= H-1;
			char ch[2],ch1[2];
			sprintf(ch,"%d",h);		//converts int to string
			sprintf(ch1,"%d",C);		//converts in to string
			char *arg[]={argv,ch,ch1,NULL};
			int ret = execvp(argv,arg);   	// error handling for exec
		
			if(ret ==-1){

				fprintf(stderr,"execvp failed\n");
				exit(1);	
			
				}
			}

			if(pid < 0){  //error handling for fork
				
				fprintf(stderr,"fork failed\n");
				exit(1);
			
			}

			else if(pid > 0){	//we are in the parent
				
				if(C-i > 1){
				
				i++;
				create_child(H,C,argv);  // recursive call
				
				}
				
				wait(NULL);	//wait function call
				printf("%d: terminating at height %d \n",pid,(H-1));
		
			}
		}
	else{
		return;  		// recusion stop condition
	}
}
void output(int H,int C){              //output	

		printf("%d: Process starting \n",getpid());
                printf("%d: Parent's id= %d \n",getpid(),getppid());
                printf("%d: Height in the tree= %d \n",getpid(),H);
                printf("%d: Creating %d children at height %d \n",getpid(),C,(H-1));
                return;

}
int main(int argc, char *argv[]){      //command line input		

	int H,C;
        pid_t ppid,pid;
        H= atoi(argv[1]);              //converts string or char array to int
        C= atoi(argv[2]);
        output(H,C);					
        create_child(H,C,argv[0]);
        return 0;

}	

