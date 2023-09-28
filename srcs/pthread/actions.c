/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:49:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/28 12:30:58 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->mutex[philo->fork_r]);
	status_time(philo, table, TEXT_FORK, 0);
	if (table->info->n_philo == 1)
	{
		pthread_mutex_unlock(&table->mutex[philo->fork_r]);
		return ;
	}
	pthread_mutex_lock(&table->mutex[philo->fork_l]);
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
	pthread_mutex_unlock(&table->mutex[philo->fork_r]);
	pthread_mutex_unlock(&table->mutex[philo->fork_l]);
	status_time(philo, table, TEXT_SLEEP, table->info->t_sleep);
	status_time(philo, table, TEXT_THINK, 0);
}
