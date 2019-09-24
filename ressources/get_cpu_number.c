#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>

int cpuNumb;
int oldCpuNumb;


int main(void)
{
  //https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
  time_t rawtime;
  struct tm *info;
  time( &rawtime );
  info = localtime( &rawtime );

  oldCpuNumb = 0;
  while(1)
  {
    cpuNumb = sched_getcpu();
    if(oldCpuNumb != cpuNumb)
    {
      time( &rawtime );
      info = localtime( &rawtime );
      oldCpuNumb = cpuNumb;
      printf("cpu number at %s : %d \n",asctime(info), cpuNumb);
    }


  }

}
