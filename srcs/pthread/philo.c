/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:04 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/25 13:40:18 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//mejorar manejo de los tenedores




/* get current time */
size_t	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	tempo(t_table *table, size_t t_slp)
{
	size_t	t;

	t = get_time();
	while (table->end == 0)
	{
		if (get_time() - t > t_slp)
			break ;
		usleep(500);
	}
}

void	status_time(t_philo *philo, t_table *table, char *status, size_t time)
{
	if (table->end == 0)
	{
		//milisleep(time, table);
		tempo(table, time);
		//philo->t_end = get_time();
		if (table->end == 0)
			printf("%06ld %d %s\n", (get_time() - table->t_start), philo->id_philo + 1, status);
			//printf("%06ld %d %s\n", time_to_milis(table->t_start, philo->t_end), philo->id_philo + 1, status);
	}
}
void ft_usleep(size_t time)
{
	usleep(time);
}
void	*thread_philo(void *data)
{
	t_philo	*philo;
	t_table	*table;
	//int		post;
	//int		actu;

	philo = (t_philo *)data;
	table = philo->table;
	//post = find_post(philo->id_philo, table->info->n_philo);
	if ((philo->id_philo) % 2 == 0)
		tempo(table, 2);
		//ft_usleep(500);
	while (table->end == 0 && philo->fin == 0)
	{
		get_fork(table, philo);
		dinner(table, philo);
		//if (philo->fin == 0)
		leave_fork(table, philo);
	}
	return (NULL);
}
