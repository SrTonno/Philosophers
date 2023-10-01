/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/29 12:43:43 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_time_die(t_table *table)
{
	int		count;

	count = -1;
	while (table->info->n_philo > ++count)
	{
		if (table->stats[count].fin == 0 && get_time() - \
			table->stats[count].t_last_eat > (size_t)table->info->t_die)
		{
			pthread_mutex_lock(&table->prot_end);
			table->end = 2;
			pthread_mutex_unlock(&table->prot_end);
			usleep(300);
			mutex_print(TEXT_DIED, &table->stats[count], table, TRUE);
			return (0);
		}
	}
	return (1);
}

static void	destroy_philo(t_table *table)
{
	int	index;

	index = 0;
	while (table->info->n_philo > index)
	{
		pthread_mutex_destroy(&table->mutex[index]);
		pthread_detach(table->philo[index++]);
	}
	pthread_mutex_destroy(&table->prot_end);
	pthread_mutex_destroy(&table->prot_print);
	free(table->philo);
	free(table->fork);
	free(table->mutex);
	free(table->stats);
}

void	*sniffer_philo(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	while (1)
	{
		if (check_time_die(table) != 1)
			break ;
		if (table->info->has_max_eat == TRUE && table->philo_eat == \
			table->info->n_philo)
		{
			table->end = 3;
			break ;
		}
		usleep(1500);
	}
	i = -1;
	while (++i < table->info->n_philo)
		pthread_join(table->philo[i], NULL);
	destroy_philo(table);
	return (NULL);
}
