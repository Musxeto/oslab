#include<stdio.h>
#include<unistd.h>

int main(){
	pid_t pid=fork();
	if(pid==0){
		printf("Child Process ID: %d\n", getpid());
	}else if(pid>0){
		printf("Fork CHild PID: %d\n",pid);
		printf("Parent PID: %d\n",getpid());
	}	
	else{
		printf("FOrk FAiled");
}
}

