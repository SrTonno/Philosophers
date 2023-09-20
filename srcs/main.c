/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/19 18:32:59 by tvillare         ###   ########.fr       */
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

/* ERRORES
muerte extraña en tiempos grandes (error de comparacion de tiempo de tiempo)
*/

static int	created_philo(t_table *table)
{
	int	count;
	int max;

	max = table->info->n_philo;
	count = -1;
	while (max > ++count)
	{
		pthread_mutex_init(&table->mutex[count], NULL);
		gettimeofday(&table->stats[count].t_last_eat, NULL);
	}
	count = 0;
	while (max > count)
	{
		if ((pthread_create(&table->philo[count++], NULL, thread_philo, table)) != 0)
		{
			printf("Error creating the thread. Code ");
			return (1);
		}
		usleep(10);
		table->id_tmp++;
	}
	sniffer_philo(table);
	count = 0;
	//while (max > count)
		//pthread_join(table->philo[count++], NULL);
	//while (table->end == 0)
		//usleep(10);
	//pthread_detach(table->sniffer);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	//int			count;

	//count = 0;
	//printf("%d\n", argc);
	table.info = check_input(argv, argc);
	if (table.info == NULL)
		return (0);
	table.id_tmp = 0;
	table.end = 0;
	table.philo = ft_calloc(table.info->n_philo + 1, sizeof(pthread_t));
	table.mutex = ft_calloc(table.info->n_philo + 1, sizeof(pthread_mutex_t));
	table.stats = ft_calloc(table.info->n_philo + 1, sizeof(t_philo));
	pthread_mutex_init(&table.prot_end, NULL);
	//printf("count philo %d / max_eat : %d\n", table.info->n_philo,  table.info->max_eat);
	gettimeofday(&table.t_start, NULL);
	if (created_philo(&table) != 0)
		return (1);
	//printf("\nSUPER \t FINNNN\n");
	return (0);
}
