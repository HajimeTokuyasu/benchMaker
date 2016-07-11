#include <time.h>
#include <stdio.h>

int main(int argv, char* argc[])
{
   time_t time1, time2;
   long l;

   time(&time1);

   for (l=0; l<100000000; l++);

   time(&time2);
   printf("INTERVAL_TIME: %fsec\n", difftime(time2,time1));

   return 0;
}

