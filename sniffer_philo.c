/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/24 17:30:31 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_time_die(t_table *table)
{
	int	count;
	struct timeval	t_stop;

	(void)table;
	count = -1;
	gettimeofday(&t_stop, NULL);
	while (table->info->n_philo > ++count)
	{
		if (time_to_milis(table->stats[count].t_last_eat, t_stop) > table->info->t_die)
		{
			printf("DIE %06ld, die in %d, philo %d, count %d", time_to_milis(table->stats[count].t_last_eat, t_stop), table->info->t_die, table->stats[count].id_philo, count);
			return (0);
		}
	}
	return (1);
}

static void destroy_philo(t_table *table)
{
	int	index;

	index = 0;
	printf("INICIO DE LA DESTRUCION\n");
	while (table->philo[index] != '\0')
		pthread_detach(table->philo[index++]);
	free (table->philo);
}
void sniffer_philo(t_table *table)
{
	(void)table;
	printf("\n\tStart sniffer\n");
	usleep(50);
	while (1)
	{
		//printf("Ronda++");
		if (check_time_die(table) != 1)
		{
			pthread_mutex_lock(&table->prot_end);
			table->end = 2;
			pthread_mutex_unlock(&table->prot_end);
			printf("\nDIE\n");
			break ;
		}
		if (table->end == 1)
		{
			printf("\nFIN de commer\n");

			break ;
		}
	}
	destroy_philo(table);
}
