/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:49:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/07/08 19:39:30 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

void swap_fork(int *a, int *b)
{
	int swap;

	if (a > b)
		return ;
	swap = *a;
	*a = *b;
	*b = swap;
}

void	get_fork(t_table *table, t_philo *philo, int post)
{
	post = find_post(philo->id_philo, table->info->n_philo);
	pthread_mutex_lock(&table->mutex[philo->fork_r]);
	status_time(philo, table, "has taken a fork", 0);
	//printf("&%d\n",philo->id_philo);
	pthread_mutex_lock(&table->mutex[philo->fork_l]);
	status_time(philo, table, "has taken a fork", 0);
	//printf("%d\n", post);
}

void	dinner(t_table *table, t_philo *philo, int post)
{
	(void) post;
	status_time(philo, table, "is eating", table->info->t_eat);
	gettimeofday(&philo->t_last_eat, NULL);
	philo->n_eat++;

	if (table->info->max_eat != 0 && table->info->max_eat == philo->n_eat)
	{
		pthread_mutex_lock(&table->prot_end);
		table->end = 1;
		pthread_mutex_unlock(&table->prot_end);
	}
}

void	leave_fork(t_table *table, t_philo *philo, int post)
{
	post = find_post(philo->id_philo, table->info->n_philo);
	pthread_mutex_unlock(&table->mutex[philo->fork_r]);
	pthread_mutex_unlock(&table->mutex[philo->fork_l]);
	status_time(philo, table, "is sleeping", table->info->t_sleep);
	status_time(philo, table, "is thinking", 0);
}
