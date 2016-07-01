//**************************The_Source_was_written_by_Tokuyasu_Hajime**************************
//**************************__________Source_Built:20160628__________**************************

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */


#include <sys/times.h>
#include <time.h>

struct timer {
   double result_usrCPU;
   double result_sysCPU;
};

static struct timer displayProc(void);

static struct timer displayProc (void){
   struct tms t;
   clock_t clockTime;
   static double clockTicks = 0;

   struct timer timer_return;

   if (clockTicks == 0){
      clockTicks = sysconf(_SC_CLK_TCK);
      if (clockTicks == -1)
         puts("sysconf");
   }//getClock_4_systemInternal
   
   clockTime = clock();
   if (clockTime == -1)
      puts("clock");
   printf("    clock() returns: %ld clock_per_sec (%.2f secs))\n",
   (long) clockTime,  clockTime/CLOCKS_PER_SEC);
   
   if (times(&t) == -1)
      puts("times");
   timer_return.result_usrCPU = (double) t.tms_utime/clockTicks;
   timer_return.result_sysCPU = (double) t.tms_stime/clockTicks;

   printf("    times() says: user_CPU=%.2f; system CPU : %.2f\n",
    timer_return.result_usrCPU  ,
    timer_return.result_sysCPU  );

   return timer_return;
}
int main( int argv,char* argc[]) {

   struct timer timer_result_start,timer_result_end,timer_voidloop_start,timer_voidloop_end;

   if (argc[1] == NULL){
      puts("\n[ERROR]::\n[USAGE]_arg1_is_numeric\n[USAGE]_arg2_is_command\n");
      return -1;
   }

   printf( "CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK) =%ld\n\n",
         (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));

   timer_result_start = displayProc();

  int i;
  int loop = atoi(argc[1]);
  for (i = 0; i< loop; i++){//
   printf("[**]Loop_%d__\n",i);
   system(argc[2]);
  }

   timer_result_end =  displayProc();

   

   printf("Then::USR_CPUproc_Interval_time_is::%f\n",timer_result_end.result_usrCPU - timer_result_start.result_usrCPU);
   printf("Then::SYS_CPUproc_Interval_time_is::%f\n",timer_result_end.result_sysCPU - timer_result_start.result_sysCPU);

   exit(EXIT_SUCCESS);
   return 0;
}
