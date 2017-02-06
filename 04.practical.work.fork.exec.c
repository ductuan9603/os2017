#include<stdio.h>
#include<unistd.h>
int main(){
printf("main before fork()\n");
int pid_1 = fork();
	if (pid_1 == 0){
		printf("I am child after fork(), launching ps -ef\n");
		char *args[]= { "/bin/ps", "-ef" , NULL};
		execvp("/bin/ps", args);
		printf("Finished launching ps -ef\n");
		}
	else { 
	printf("I am parent after fork(), child is %d\n", pid_1);
	int pid_2 = fork();
	if (pid_2 == 0){
		printf("I am a child after fork(), lauching free -h\n");
		char *args[] = {"/bin/free","-h",NULL};
		execvp("/usr/bin/free",args);
		printf("finish lauching free -h\n");
		}
	else {
	printf("I am parent after fork(), child is %d\n", pid_2);}
	}
return 0;
}
