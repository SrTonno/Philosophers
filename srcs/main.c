/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/10/27 15:09:08 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct(t_table *table)
{
	free(table->philo);
	free(table->info);
	free(table->fork);
	free(table->mutex);
	free(table->stats);
}
static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

void	set_info_philo(t_philo *philo, t_table *table, int id)
{
	philo->id_philo = id;
	table->fork[id] = 0;
	philo->fork_r = philo->id_philo;
	philo->fork_l = find_post(philo->id_philo, table->info->n_philo);
	philo->n_eat = 0;
	philo->fin = 0;
	philo->table = table;
	philo->t_last_eat = table->t_start;
}

static int	created_philo(t_table *table)
{
	int	count;
	int	max;

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
		{
			printf("Error creating the thread. Code ");
			return (1);
		}
	}
	sniffer_philo(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;

	table.info = check_input(argv, argc);
	if (table.info == NULL)
		return (0);
	table.end = 0;
	table.philo = ft_calloc(table.info->n_philo + 1, sizeof(pthread_t));
	table.mutex = ft_calloc(table.info->n_philo + 1, sizeof(pthread_mutex_t));
	table.stats = ft_calloc(table.info->n_philo + 1, sizeof(t_philo));
	table.fork = ft_calloc(table.info->n_philo + 1, sizeof(int));
	if (table.stats == NULL || table.philo == NULL || table.stats == NULL
		|| table.fork == NULL)
	{
		free_struct(&table);
		return (1);
	}
	table.philo_eat = 0;
	pthread_mutex_init(&table.prot_end, NULL);
	pthread_mutex_init(&table.prot_print, NULL);
	if (created_philo(&table) != 0)
		return (free_struct(&table), 1);
	system("leaks -q philo");
	return (0);
}
