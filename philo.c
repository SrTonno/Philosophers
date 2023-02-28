/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:04 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/28 15:08:59 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//mejorar manejo de los tenedores
static int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

void	status_time(t_philo *philo, t_table *table, char *status, int time)
{
	if (table->end == 0)
	{
		milisleep(time, table);
		gettimeofday(&philo->t_end, NULL);
		if (table->end == 0)
			printf("%06ld %d %s\n", time_to_milis(table->t_start, philo->t_end), philo->id_philo + 1, status);
	}
}

void	*thread_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;
	int		post;
	int		id;

	table = (t_table *)data;
	id = table->id_tmp;
	philo = &table->stats[id];
	philo->id_philo = id;

	philo->n_eat = 0;
	post = find_post(philo->id_philo, table->info->n_philo);
	//printf("Philo %d-%d\n", philo->id_philo, post);
	gettimeofday(&table->stats[id].t_last_eat, NULL);
	if (philo->id_philo + 1 / 2 == 0)
		usleep(100);
	while (table->end == 0)
	{
		get_fork(table, philo, post);
		dinner(table, philo, post);
		leave_fork(table, philo, post);
	}
	//table->end = 1;
	//printf("\n \t FIN\n");
	return (NULL);
}
