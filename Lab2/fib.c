#include "types.h"
#include "user.h"

int fib(int n){
// printf(1,"n = %d",n); 
 if(n < 1) return (1); 
  else
  return(fib(n-1) + fib(n-2));
}


int 
main( int argc, char *argv[]){
	
	if(argc < 2) {
		printf(1,"fib (fib number) \n");
		exit();
	}else{
		int n = atoi(argv[1]);
	        printf(1,"Calculating %d\n",n);
		n = fib(n);
		printf(1,"Fibonacci sum : %d\n",n);
        	exit();
	}
}
