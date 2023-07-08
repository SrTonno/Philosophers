/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/07/08 13:20:56 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_time_die(t_table *table)
{
	int				count;
	struct timeval	t_stop;

	(void)table;
	count = -1;
	gettimeofday(&t_stop, NULL);
	while (table->id_tmp > ++count)
	{
		if (time_to_milis(table->stats[count].t_last_eat, t_stop) > table->info->t_die)
		{
			status_time(&table->stats[count], table, "died", 0);
			printf("DIE %06ld, die in %d, philo %d, count %d, eat %d", time_to_milis(table->stats[count].t_last_eat, t_stop), table->info->t_die, table->stats[count].id_philo + 1, count + 1, table->stats[count].n_eat);
			//printf("\ntime eat %d, sleep %d\n", table->info->t_eat, table->info->t_sleep);
			return (0);
		}
	}
	return (1);
}

static void destroy_philo(t_table *table)
{
	int	index;

	index = 0;
	//printf("INICIO DE LA DESTRUCION\n");
	while (table->info->n_philo >= index)
		pthread_detach(table->philo[index++]);
	free (table->philo);
}
void	*sniffer_philo(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	(void)table;
	usleep(5000);
	while (1)
	{
		//printf("Ronda++");
		if (check_time_die(table) != 1)
		{
			pthread_mutex_lock(&table->prot_end);
			table->end = 2;
			pthread_mutex_unlock(&table->prot_end);
			break ;
		}
		if (table->end == 1)
		{
			//printf("\nFIN de commer\n");
			break ;
		}
		usleep(3000);
	}
	destroy_philo(table);
	return (NULL);
}
