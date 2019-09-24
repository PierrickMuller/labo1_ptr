#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>

#define EXECUTION_TIME    10/*In seconds*/

/*Barrier variable*/
pthread_barrier_t barr;

void *f_thread(void *arg)
{
  /*...*/
}
int main(int argc,char **argv)
{
  /*...*/

  /*Parse input*/
  if(argc != 2)
  {
    fprintf(stderr, "Usage: %s NB_THREADS\n", argv[0]);
    return EXIT_FAILURE;
  }
  nb_threads = strtoimax(argv[1], (char **)NULL, 10);
  if(nb_threads <= 0)
  {
    fprintf(stderr, "NB_THREADS must be > 0 (actual: %d)\n", nb_threads);
    return EXIT_FAILURE;
  }

  /*...*/

  /*Get minimal and maximal priority values*/
  min_prio = sched_get_priority_min(SCHED_FIFO);
  max_prio = sched_get_priority_max(SCHED_FIFO);
  max_prio -= min_prio;

  /*Initialize barrier*/
  if(pthread_barrier_init(&barr, NULL, nb_threads))
  {
    fprintf(stderr, "Could not initialize barrier!\n");
    return EXIT_FAILURE;
  }

  /*Set priorities and create threads*/


  /*Wait for the threads to complete and set the results*/

  /*...*/

  for(i = 0; i < nb_threads; ++i)
  {
    fprintf(stdout, "[%02d] %ld (%2.0f%%)\n",
    prio_value[i], nb_iterations[i],
    100.0*nb_iterations[i] / total_iterations);
  }

  return EXIT_SUCCESS;
}
