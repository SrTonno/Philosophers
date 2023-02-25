/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:04 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/25 18:38:49 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

static void	status_time(t_philo *philo, t_table *table, char *status, int time)
{
	if (table->end == 0)
	{
		usleep((time * 1000));
		gettimeofday(&philo->t_end, NULL);
		if (table->end == 0)
			printf("%06ld %d %s %d\n", time_to_milis(table->t_start, philo->t_end), philo->id_philo, status, philo->n_eat);
	}
}

void	*thread_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int		post;
	int		id;

	table = (t_table *)data;
	id = table->id_tmp;
	philo = &table->stats[id];
	philo->id_philo = id;

	philo->n_eat = 0;
	post = find_post(philo->id_philo, table->info->n_philo);
	//printf("Philo %d-%d\n", philo->id_philo, post);
	gettimeofday(&table->stats[id].t_last_eat, NULL);
	if (philo->id_philo / 2 == 0)
		usleep(40);
	while (table->end == 0)
	{
		pthread_mutex_lock(&table->mutex[philo->id_philo]);
		status_time(philo, table, "has taken a fork", 0);
		pthread_mutex_lock(&table->mutex[post]);
		status_time(philo, table, "has taken a fork", 0);
		status_time(philo, table, "is eating", table->info->t_eat);
		gettimeofday(&philo->t_last_eat, NULL);
		philo->n_eat++;
		if (table->info->max_eat != 0 && table->info->max_eat == philo->n_eat)
		{
			pthread_mutex_lock(&table->prot_end);
			table->end = 1;
			pthread_mutex_unlock(&table->prot_end);
		}
		pthread_mutex_unlock(&table->mutex[philo->id_philo]);
		pthread_mutex_unlock(&table->mutex[post]);
		status_time(philo, table, "is sleeping", table->info->t_sleep);
		status_time(philo, table, "is thinking", 0);
		//printf("Philo %d-%d\n", philo->id_philo, post);
	}
	//table->end = 1;
	printf("\n \t FIN\n");
	return (NULL);
}
