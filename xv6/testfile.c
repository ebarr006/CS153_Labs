#include "types.h"
#include "user.h"
//#include "defs.h"
int 
main( int argc, char **argv){
	
	printf(1, "Test for exit, wait, and waitpid syscals ;) \n");
	
	int pid1 = fork();
	
	printf(1,"First pid: %d\n",pid1);
	
	if(pid1 == 0 ){
		
		wait(0);	
		printf(1,"Parent1 with child pid: %d \n", pid1);
	}else{
		int pid2 = fork();
	        
		//waitpid(pid2, 0 , 0);
		if(pid2 == 0){
			wait(0);
			printf(1,"child with pid: %d \n",pid1);
		}else{
			printf(1,"child2 pid: %d\n",pid2);
		}	
	}
	

	//exit(0);

}
