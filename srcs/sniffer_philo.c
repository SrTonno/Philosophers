/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/23 19:25:26 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_time_die(t_table *table)
{
	int		count;
	int		id;
	size_t	time;
	//struct timeval	t_stop;

	(void)table;
	count = -1;
	//gettimeofday(&t_stop, NULL);
	while (table->id_tmp > ++count)
	{
		if (table->stats[count].fin == 0 && get_time() - table->stats[count].t_last_eat > (size_t)table->info->t_die)
		{
			id = table->stats[count].id_philo + 1;
			time = get_time() - table->t_start;
			pthread_mutex_lock(&table->prot_end);
			table->end = 2;
			pthread_mutex_unlock(&table->prot_end);
			//usleep (1000);
			printf("%06ld %d %s\n", time, id, "died");
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
	int	i;

	table = (t_table *)data;
	(void)table;
	usleep(5000);
	while (1)
	{
		//printf("eat -> %d max ->%d \n", table->end, table->info->max_eat);
		if (check_time_die(table) != 1)
		{
			break ;
		}
		if (table->info->max_eat != 0 && table->end == table->info->n_philo)
		{
			printf("\nFIN de commer\n");
			table->end = 3;
			break ;
		}
		usleep(4000);
	}
	i = -1;
	while (++i < table->info->n_philo)
		pthread_join(table->philo[i], NULL);
	//if (table->end == 20)
	destroy_philo(table);
	return (NULL);
}
