/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 18:49:02 by tvillare          #+#    #+#             */
/*   Updated: 2023/03/01 11:06:21 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_table *table, t_philo *philo, int post)
{
	pthread_mutex_lock(&table->mutex[philo->id_philo]);
	status_time(philo, table, "has taken a fork", 0);
	printf("%d\n", philo->id_philo);
	pthread_mutex_lock(&table->mutex[post]);
	status_time(philo, table, "has taken a fork", 0);
	printf("%d\n", post);
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
	pthread_mutex_unlock(&table->mutex[philo->id_philo]);
	pthread_mutex_unlock(&table->mutex[post]);
	status_time(philo, table, "is sleeping", table->info->t_sleep);
	status_time(philo, table, "is thinking", 0);
}
