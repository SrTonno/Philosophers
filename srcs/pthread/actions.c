/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:49:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/22 13:09:28 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}*/

void	get_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->mutex[philo->fork_r]);
	status_time(philo, table, TEXT_FORK, 0);
	pthread_mutex_lock(&table->mutex[philo->fork_l]);
	status_time(philo, table, TEXT_FORK, 0);
}

void	dinner(t_table *table, t_philo *philo)
{
	status_time(philo, table, TEXT_DINNER, table->info->t_eat);
	//gettimeofday(&philo->t_last_eat, NULL);
	philo->t_last_eat = get_time();
	philo->n_eat++;
	if (table->info->max_eat != 0 && table->info->max_eat == philo->n_eat)
	{
		pthread_mutex_lock(&table->prot_end);
		table->end = 1;
		pthread_mutex_unlock(&table->prot_end);
	}
}

void	leave_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_unlock(&table->mutex[philo->fork_r]);
	pthread_mutex_unlock(&table->mutex[philo->fork_l]);
	status_time(philo, table, TEXT_SLEEP, table->info->t_sleep);
	status_time(philo, table, TEXT_THINK, 0);
}
