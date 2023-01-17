/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:45:00 by tvillare          #+#    #+#             */
/*   Updated: 2023/01/17 14:46:02 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info	*save_info(char **data, int count)
{
	t_info *info;

	info = malloc(1 * sizeof(t_info));
	info->n_philo = ft_atoi(data[1]);
	info->t_die = ft_atoi(data[2]);
	info->t_eat = ft_atoi(data[3]);
	info->t_sleep = ft_atoi(data[4]);
	if (count == 6)
		info->max_eat = ft_atoi(data[5]);
	else
		info->max_eat = 0;
	return (info);
}

static int	created_philo(t_table *table)
{
	int	count;

	count = 0;
	//printf("n%d", table->info->n_philo);
	while (table->info->n_philo > count)
	{
		pthread_mutex_init(&table->mutex[count], NULL);
		if ((pthread_create(&table->philo[count++], NULL, thread_philo, table)) != 0)
		{
			printf("Error creating the thread. Code ");
			return (1);
		}
		usleep(10);
		table->id_tmp++;
	}
	count = 0;
	while (table->info->n_philo > count)
		pthread_join(table->philo[count++], NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table		table;
	int			count;

	count = 0;
	printf("%d\n", argc);
	if (argc < 5 || argc > 6)
	{
		printf("Error:\n nummeros de parametros incorrectos");
		return (1);
	}
	table.info = save_info(argv, argc);
	table.id_tmp = 0;
	table.philo = malloc(table.info->n_philo + 1 * sizeof(pthread_t));
	table.mutex = malloc(table.info->n_philo + 1 * sizeof(pthread_mutex_t));
	/*while (table.info->n_philo > count)
	{
		printf("%d\n", count);
		pthread_mutex_init(&table.mutex[count++], NULL);
	}*/
	if (created_philo(&table) != 0)
		return (1);
	
	return (0);
}
