/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/25 18:05:46 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
1 800 200 200 muere
5 800 200 200 viven
5 800 200 200 7 viven y cada uno come 7 veces
4 410 200 200 viven
4 310 200 100 mueren
*/
static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

void	set_fork(t_philo *philo, t_table *table)
{
	if (philo->id_philo == 0)
	{
		philo->fork_r = find_post(philo->id_philo, table->info->n_philo);
		philo->fork_l = 0;
		return ;
	}
	philo->fork_r = philo->id_philo;
	philo->fork_l = find_post(philo->id_philo, table->info->n_philo);
}

void	set_info_philo(t_philo *philo, t_table *table, int id)
{
	philo->id_philo = id;
	set_fork(philo, table);
	philo->n_eat = 0;
	philo->fin = 0;
	philo->table = table;
	philo->t_last_eat = get_time();
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
	pthread_mutex_init(&table.prot_end, NULL);
	if (created_philo(&table) != 0)
		return (1);
	return (0);
}
