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


struct tms t;
clock_t clockTime;
long clockTicks = 0;
struct tms timer_return,timer_result_start,timer_result_end;

struct tms getTime (void){
   if (clockTicks == 0){
      clockTicks = sysconf(_SC_CLK_TCK);
      if (clockTicks == -1)
         puts("sysconf");
   }//getClock_4_systemInternal
   
   clockTime = clock();
   if (clockTime == -1)
      puts("clock");
   printf("    clock() returns: %ld clock_per_sec (%.2f secs))\n",
   (long) clockTime, (double) clockTime/CLOCKS_PER_SEC);

   return t;
}

int main( int argv,char* argc[]) {

   if (argc[1] == NULL){
      puts("\n[ERROR]::\n[USAGE]_arg1_is_numeric\n[USAGE]_arg2_is_command_without_arg\n");
      return -1;
   }

   
   if (times(&t) == -1)
      puts("times");
   printf( "CLOCKS_PER_SEC=%ld sysconf(_SC_CLK_TCK) =%ld\n\n",
         (long) CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK));
   
   timer_result_start = getTime();

  int i;
  int loop = atoi(argc[1]);
  for (i = 0; i< loop; i++){//
   system(argc[2]);
  }

   timer_result_end =  getTime();

   puts("[NOTE]The_time_is_SYSTEMTIME");
   printf("Then::USR_CPUproc_Interval_time_is::%f\n",(double)timer_result_end.tms_utime - timer_result_start.tms_utime);
   printf("Then::SYS_CPUproc_Interval_time_is::%f\n",(double)timer_result_end.tms_stime - timer_result_start.tms_stime);
   printf("Thus::USR_CPUproc_time@OneLoop_is::%f\n",(double)(timer_result_end.tms_utime - timer_result_start.tms_utime) / (atoi)argc[2]);
   printf("Thus::SYS_CPUproc_time@OneLoop_is::%f\n",(double)timer_result_end.tms_stime - timer_result_start.tms_stime / (atoi)argc[2];

   exit(EXIT_SUCCESS);
   return 0;
}
