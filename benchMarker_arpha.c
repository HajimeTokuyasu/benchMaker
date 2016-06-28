#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
 plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */


#include <sys/times.h>
#include <time.h>
static void displayProc (const char *msg){
      struct tms t;
      clock_t clockTime;
      static long clockTicks = 0;

      if (msg != NULL)
         printf("%s", msg);
      if (clockTicks == 0){
         clockTicks = sysconf(_SC_CLK_TCK);
         if (clockTicks == -1)
            puts("sysconf");
      }
      
      clockTime = clock();
      if (clockTime == -1)
         puts("clock");
      printf("    clock() returns: %ld clock_per_sec (%.2f secs))\n",
      (long) clockTime, (double) clockTime/CLOCKS_PER_SEC);
      
      if (times(&t) == -1)
         puts("times");

      printf("    times() says: user_CPU=%.2f; system CPU : %.2f\n",
         (double) t.tms_utime/clockTicks,
         (double) t.tms_stime/clockTicks);
}
int main( int argv,char* argc[]) {

   int numCalls, j;


   if (argc[1] == NULL){
      puts("ERROR::usage_arg1_is_numeric");
      return -1;
   }

   printf( "CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK) =%ld\n\n",
         (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

   displayProc("At programvstart:\n");
   numCalls = atoi(argc[1]);
   for ( j = 0; j < numCalls; j++)
         (void) getppid();
   displayProc("After getppid() loop:\n");
   exit(EXIT_SUCCESS);
   return 0;
}
