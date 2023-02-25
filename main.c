/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/25 13:43:48 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//se asicio id incorecto incorrecto al philo
static int	created_philo(t_table *table)
{
	int	count;
	int max;

	max = table->info->n_philo;
	count = 0;
	printf("\ncount philo %d\n", max);
	while (max > count)
	{
		//table->stats[count].id_philo = table->id_tmp;
		pthread_mutex_init(&table->mutex[count], NULL);
		if ((pthread_create(&table->philo[count++], NULL, thread_philo, table)) != 0)
		{
			printf("Error creating the thread. Code ");
			return (1);
		}
		usleep(200);
		table->id_tmp++;
	}
	sniffer_philo(table);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			count;

	count = 0;
	printf("%d\n", argc);
	table.info = check_input(argv, argc);
	if (table.info == NULL)
		return (0);
	table.id_tmp = 0;
	table.end = 0;
	table.philo = ft_calloc(table.info->n_philo + 1, sizeof(pthread_t));
	table.mutex = ft_calloc(table.info->n_philo + 1, sizeof(pthread_mutex_t));
	table.stats = ft_calloc(table.info->n_philo + 1, sizeof(t_philo));
	pthread_mutex_init(&table.prot_end, NULL);
	printf("count philo %d / max_eat : %d\n", table.info->n_philo,  table.info->max_eat);
	gettimeofday(&table.t_start, NULL);
	if (created_philo(&table) != 0)
		return (1);
	printf("\nSUPER \t FINNNN\n");
	return (0);
}
