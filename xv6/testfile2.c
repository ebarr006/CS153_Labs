#include "types.h"
#include "user.h"

int 
main( int argc, char **argv){
	
	printf(1, "Test for exit, wait, and waitpid syscals ;) \n \n");
	
	int pid1 = fork();
	//wait(0);
	printf(1,"First pid: %d\n\n",pid1);
	
	if(pid1 == 0 ){
			
		printf(1,"Parent1 with child pid: %d \n\n", pid1);
		
	
	}else{
		
	        

		printf(1,"child with pid: %d \n\n",pid1);
		
			
	}
	

	exit(0);

}
