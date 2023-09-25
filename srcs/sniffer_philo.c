/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/25 18:04:10 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_time_die(t_table *table)
{
	int		count;
	int		id;
	size_t	time;

	count = -1;
	while (table->info->n_philo > ++count)
	{
		if (table->stats[count].fin == 0 && get_time() - \
			table->stats[count].t_last_eat > (size_t)table->info->t_die)
		{
			id = table->stats[count].id_philo + 1;
			time = get_time() - table->t_start;
			pthread_mutex_lock(&table->prot_end);
			table->end = 2;
			pthread_mutex_unlock(&table->prot_end);
			printf("%06ld %d %s\n", time, id, "died");
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
		pthread_detach(table->philo[index++]);
	free (table->philo);
}

void	*sniffer_philo(void *data)
{
	t_table	*table;
	int		i;

	table = (t_table *)data;
	(void)table;
	while (1)
	{
		if (check_time_die(table) != 1)
			break ;
		if (table->info->max_eat > 0 && table->philo_eat == \
			table->info->n_philo)
		{
			table->end = 3;
			break ;
		}
		usleep(1000);
	}
	i = -1;
	while (++i < table->info->n_philo)
		pthread_join(table->philo[i], NULL);
	destroy_philo(table);
	return (NULL);
}
