/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:04:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/01/17 14:47:37 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	find_post(int id, int max)
{
	if (id == 0)
		return (max);
	return (id - 1);
}
void	*thread_philo(void *data)
{
	t_philo	philo;
	t_table	*table;
	int		post;

	table = (t_table *)data;
	philo.id_philo = table->id_tmp;
	philo.n_eat = 0;
	post = find_post(philo.id_philo, table->info->n_philo);
	//usleep(10);
	printf("Philo %d\n", philo.id_philo);
	if (philo.id_philo / 2 == 0)
		usleep(40);
	gettimeofday(&philo.t_start, NULL);
	while (table->info->max_eat > philo.n_eat)
	{

		pthread_mutex_lock(&table->mutex[philo.id_philo]);
		printf("timestamp_in_ms %d has taken a fork/ 1 %d\n", philo.id_philo, philo.n_eat);
		pthread_mutex_lock(&table->mutex[post]);
		printf("timestamp_in_ms %d has taken a fork/ 2 %d\n", philo.id_philo, philo.n_eat);
		usleep(table->info->t_eat);
		printf("timestamp_in_ms %d is eating %d\n", philo.id_philo, philo.n_eat);
		philo.n_eat++;
		pthread_mutex_unlock(&table->mutex[philo.id_philo]);
		pthread_mutex_unlock(&table->mutex[post]);
		usleep(table->info->t_sleep);
		printf("timestamp_in_ms %d is sleeping %d\n", philo.id_philo, philo.n_eat);
		printf("timestamp_in_ms %d is thinking %d\n", philo.id_philo, philo.n_eat);
	}
	return (NULL);
}
