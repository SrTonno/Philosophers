/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:49:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/10/26 12:13:51 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	take_fork(pthread_mutex_t *mutex, int *fork)
{
	while(*fork == 1)
		usleep(50);
	pthread_mutex_lock(mutex);
	*fork = 1;
	pthread_mutex_unlock(mutex);
}

void	release_fork(pthread_mutex_t *mutex, int *fork)
{
	pthread_mutex_lock(mutex);
	*fork = 0;
	pthread_mutex_unlock(mutex);
}


void	get_fork(t_table *table, t_philo *philo)
{
	take_fork(&table->mutex[philo->fork_r] , &table->fork[philo->fork_r]);
	status_time(philo, table, TEXT_FORK, 0);
	if (table->info->n_philo == 1)
	{
		release_fork(&table->mutex[philo->fork_r], &table->fork[philo->fork_r]);
		//table->fork[philo->fork_r] = 0;
		//pthread_mutex_unlock(&table->mutex[philo->fork_r]);
		return ;
	}
	take_fork(&table->mutex[philo->fork_l] , &table->fork[philo->fork_l]);
	status_time(philo, table, TEXT_FORK, 0);
}

void	dinner(t_table *table, t_philo *philo)
{
	status_time(philo, table, TEXT_DINNER, table->info->t_eat);
	philo->t_last_eat = get_time();
	philo->n_eat++;
	if (table->info->has_max_eat == TRUE && \
		table->info->max_eat == philo->n_eat && \
		philo->fin == 0)
	{
		pthread_mutex_lock(&table->prot_end);
		table->philo_eat++;
		philo->fin = 1;
		pthread_mutex_unlock(&table->prot_end);
	}
}

void	leave_fork(t_table *table, t_philo *philo)
{

	release_fork(&table->mutex[philo->fork_r], &table->fork[philo->fork_r]);
	release_fork(&table->mutex[philo->fork_l], &table->fork[philo->fork_l]);
	status_time(philo, table, TEXT_SLEEP, table->info->t_sleep);
	status_time(philo, table, TEXT_THINK, 0);
}
