/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:33:04 by tvillare          #+#    #+#             */
/*   Updated: 2023/07/08 19:59:08 by tvillare         ###   ########.fr       */
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

void grt_fork(t_philo *philo, t_table *table)
{
	if (philo->id_philo == 0)
	{
		philo->fork_r = find_post(philo->id_philo, table->info->n_philo);
		philo->fork_l = 0;
		return ;
	}
	philo->fork_r = philo->id_philo;
	philo->fork_l = find_post(philo->id_philo, table->info->n_philo);;

}

void	ft_usleep(int i)
{
	usleep(i);
}

void	status_time(t_philo *philo, t_table *table, char *status, int time)
{
	if (table->end == 0)
	{
		//milisleep(time, table);
		ft_usleep(time * 1000);
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
	//int		actu;
	int		id;

	table = (t_table *)data;
	id = table->id_tmp;
	philo = &table->stats[id];
	philo->id_philo = id;
	philo->n_eat = 0;
	post = find_post(philo->id_philo, table->info->n_philo);
	//gettimeofday(&table->stats[id].t_last_eat, NULL);
	//printf("Philo %d-%d\n", philo->id_philo, post);
	grt_fork(philo, table);
	printf("Philo %d-%d  //  %d-%d\n", philo->fork_r, philo->fork_l, philo->id_philo, post);
	if ((philo->id_philo + 1) / 2 == 0)// slep no funcioa en hilos
		ft_usleep(80);
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
