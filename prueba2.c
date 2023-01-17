// compile with $ gcc -Wall -g *.c -pthread -o program
// run with ./program
// check with valgrind --tool=helgrind ./program
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "philo.h"

float time_diff(struct timeval *start, struct timeval *end)
{
	return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}

void thread_run(void *data)
{
	t_table			*table;
	t_philo			philo;
	int				i;
	struct timeval	start;
	struct timeval	end;
	int	a;

	i = 10;
	table = (t_table *)data;
	philo.id_philo = table->id_tmp;
	sleep(2);
	printf("[TH_%d %ld]: Hello, soy philo \n",philo.id_philo, pthread_self());
	gettimeofday(&start, NULL);
	while (i--)
	{
		pthread_mutex_lock(&table->mutex[0]);
		pthread_mutex_lock(&table->mutex[1]);
		//printf("%d\n", a);
		table->fork++;
		gettimeofday(&end, NULL);
		printf("[TH_%d %ld]: Philo cominedo fork %d/%d in time %0.8f sec \n",philo.id_philo, pthread_self(), table->fork, i, time_diff(&start, &end));
		gettimeofday(&start, NULL);
		pthread_mutex_unlock(&table->mutex[1]);
		pthread_mutex_unlock(&table->mutex[0]);

		sleep(1);
	}

	sleep(1);
	printf("[TH_%d %ld]: To exit...............\n",philo.id_philo, pthread_self());
}

int main()
{
	t_table		table;
	int			i;
	int			max;

	max = 10;
	i = 0;

	table.philo = malloc(max + 1 * sizeof(pthread_t));
	table.mutex = malloc(max + 1 * sizeof(pthread_mutex_t));
	table.id_tmp = 0;
	printf("[MAIN %ld]: Starting............ \n",pthread_self());
	while (max > i)
	{
		pthread_mutex_init(&table.mutex[i++], NULL);
	}
	i = 0;
	while (max > i)
	{
		//pthread_mutex_init(&table.mutex[i], NULL);
		if ((pthread_create(&table.philo[i++] ,NULL,thread_run, &table))!=0)
		{
			printf("Error creating the thread. Code ");
			return -1;
		}
		usleep(10);
		table.id_tmp++;
	}
  sleep(1);
  printf("[MAIN %ld]: Thread allocated \n",pthread_self());
  i = 0;
  while (max > i)
  {
 	 pthread_join(table.philo[i++], NULL);
  }
  printf("[MAIN %ld]: End the philos \n",pthread_self());
  return 0;
}
