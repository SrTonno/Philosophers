#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int count = 10;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void	*th1_routine(void *unused)
{
	int	i;

	i = 0;
	while (i++ < 1000)
	{
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
}

void	*th2_routine(void *unused)
{
	int	i;

	i = 0;
	while (i++ < 1000)
	{
		pthread_mutex_lock(&mutex);
		count--;
		pthread_mutex_unlock(&mutex);
	}
}

int main()
{
	pthread_t	thread1;
	pthread_t	thread2;

	if(pthread_create(&thread1, NULL, th1_routine, NULL) !=0)
		printf("hilo 1 no creado");
	if(pthread_create(&thread2, NULL, th2_routine, NULL) !=0)
		printf("hilo 2 no creado");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("COUNT = %d", count);
	return (0);
}
