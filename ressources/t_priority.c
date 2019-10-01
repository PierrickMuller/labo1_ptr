#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>

#define EXECUTION_TIME    10/*In seconds*/


/*Barrier variable*/
pthread_barrier_t barr;

/*Variables */
int nb_threads;
unsigned int min_prio;
unsigned int max_prio;
unsigned int i;
unsigned total_iterations;

unsigned int *prio_value;
long int *nb_iterations;

pthread_t *threads;



float testVal;

void comptNbIter();

void *f_thread(void *arg)
{
  //récupération ID et affichage
  int id = *((int *) arg);
  printf("%d\n",id);
  //On attend tous les threads
  pthread_barrier_wait(&barr);
  comptNbIter(id);
  return NULL;
}
int main(int argc,char **argv)
{


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

  /*Allocation des ressources*/
  threads = malloc(nb_threads*sizeof(pthread_t));
  prio_value = malloc(nb_threads*sizeof(unsigned int));
  nb_iterations = malloc(nb_threads*sizeof(long int));

  //Mise en place des prioritées
  for(i=0; i < nb_threads;++i)
  {
    prio_value[i] = rand() % max_prio + 1;
    pthread_setschedprio(threads[i], prio_value[i]);
  }

  //Création des threads
  for(i=0;i < nb_threads;++i)
  {
    int *arg = malloc(sizeof(*arg));
    *arg = i;
    if(pthread_create(&threads[i], NULL, f_thread, arg) != 0)
    {
      perror("thread creation error");
      return EXIT_FAILURE;
    }
  }


  /*Wait for the threads to complete and set the results*/
  for(i = 0; i < nb_threads; i++)
  {
    pthread_join(threads[i],NULL);
  }

  //Comptage nombre total d'itérations
  for(i=0; i < nb_threads; i++)
  {
    total_iterations += nb_iterations[i];
  }

  //Affichage du résultat
  for(i = 0; i < nb_threads; ++i)
  {
    fprintf(stdout,"%d\n",prio_value[i]);
    fprintf(stdout, "[%02d] %ld (%2.0f%%)\n",
    prio_value[i], nb_iterations[i],
    100.0*nb_iterations[i] / total_iterations);
  }

  return EXIT_SUCCESS;
}


void comptNbIter(int i)
{
  //initialisation
  time_t start_time;
  time_t temp_time;
  unsigned int nb_iterations_thread;
  unsigned int nb_iterations_sec;
  unsigned int nb_sec_iter;

  nb_sec_iter = 1;
  nb_iterations_thread = 0;
  nb_iterations_sec = 0;
  start_time = time(NULL);
  temp_time = start_time;

  while(time(NULL) < (start_time + EXECUTION_TIME)) {
    //Pour affichage toutes les secondes
    if(temp_time + 1 <= time(NULL))
    {
      temp_time = time(NULL);
      printf("nb iterations sec %d : 0x%x \n",nb_sec_iter++,nb_iterations_sec);
      nb_iterations_thread += nb_iterations_sec;
      nb_iterations_sec = 0;
    }

    ++nb_iterations_sec;
  }

  //On s'assure qu'on a bien ajouter le nombre d'iterations de la dernière seconde
  if(nb_sec_iter == EXECUTION_TIME)
  {
    nb_iterations_sec = 0;
  }
  //Stockage nombre itérations
  nb_iterations[i] = nb_iterations_thread;

  printf("nb iterations tot (hex): 0x%x \n", nb_iterations_thread);
}
