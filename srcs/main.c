/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/10/27 17:38:21 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

int	error_pthread(t_table *table, int max)
{
	int	i;

	i = -1;
	table->end = 4;
	while (++i < max)
		pthread_join(table->philo[i], NULL);
	printf("Error\n\tcreating the thread");
	return (1);
}

static int	created_philo(t_table *table)
{
	int	count;
	int	max;
	int	i;

	i = -1;
	max = table->info->n_philo;
	count = -1;
	table->t_start = get_time();
	while (max > ++count)
	{
		pthread_mutex_init(&table->mutex[count], NULL);
		table->fork[count] = 0;
		set_info_philo(&table->stats[count], table, count);
	}
	count = -1;
	while (max > ++count)
	{
		if ((pthread_create(&table->philo[count], NULL, \
			thread_philo, &table->stats[count]) != 0))
			return (error_pthread(table, count));
	}
	sniffer_philo(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;

	table.end = 0;
	table.info = check_input(argv, argc);
	if (table.info == NULL)
		return (1);
	table.philo = ft_calloc(table.info->n_philo + 1, sizeof(pthread_t));
	table.mutex = ft_calloc(table.info->n_philo + 1, sizeof(pthread_mutex_t));
	table.stats = ft_calloc(table.info->n_philo + 1, sizeof(t_philo));
	table.fork = ft_calloc(table.info->n_philo + 1, sizeof(int));
	if (table.stats == NULL || table.philo == NULL || table.stats == NULL
		|| table.fork == NULL)
	{
		free_struct(&table);
		return (0);
	}
	table.philo_eat = 0;
	pthread_mutex_init(&table.prot_end, NULL);
	pthread_mutex_init(&table.prot_print, NULL);
	if (created_philo(&table) != 0)
		return (free_struct(&table), 1);
	return (0);
}
