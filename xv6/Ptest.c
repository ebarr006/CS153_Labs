#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

void
pmain( int argc, char *argv[])
{
   int k, n, pid;
   double x = 0, z, d;

   if(argc < 2)
	n = 1;
   else
        n = atoi (argv[1]);
   if (n < 0 || n > 63)
        n = 50;
 
   if( argc < 3)
     d = 0.1;
   else 
     d = atoi( argv[2]);

  x = 0;
  pid = 0;
  for(k = 0; k < n; k++){
     pid = fork();
     if( pid < 0){
        printf(1, "%d failded to fork!\n",getpid() );
     }else if(pid > 0){
	printf(1, "Parent %d creating child %d\n", getpid(), pid);
        wait(0);
     }else{
        printf(1, "child %d created\n", getpid() ); 
        for( z = 0 ; z < 999999999.0; z+=d )
            x = x +1 *99.93; 
        break;
     }

  } 
  exit(0);

}
