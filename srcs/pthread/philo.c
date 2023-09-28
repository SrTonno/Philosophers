/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:04 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/28 11:04:48 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* get current time */
size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	tempo(t_table *table, size_t t_slp)
{
	size_t	t;

	t = get_time();
	while (table->end == 0)
	{
		if (get_time() - t > t_slp)
			break ;
		usleep(100);
	}
}

void	status_time(t_philo *philo, t_table *table, char *status, size_t time)
{
	tempo(table, time);
	if (table->end == 0)
		mutex_print(status, philo, table, FALSE);
}

void	*thread_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)data;
	table = philo->table;
	if ((philo->id_philo) % 2 != 0)
		tempo(table, 2);
	while (table->end == 0)
	{
		get_fork(table, philo);
		if (table->info->n_philo == 1)
			return (NULL);
		dinner(table, philo);
		leave_fork(table, philo);
	}
	return (NULL);
}
