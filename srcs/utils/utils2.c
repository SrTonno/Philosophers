/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:33:49 by tvillare          #+#    #+#             */
/*   Updated: 2023/10/27 17:34:49 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_struct(t_table *table)
{
	free(table->philo);
	free(table->info);
	free(table->fork);
	free(table->mutex);
	free(table->stats);
}

int	find_post(int id, int max)
{
	if (id == 0)
		return (max - 1);
	return (id - 1);
}

void	set_info_philo(t_philo *philo, t_table *table, int id)
{
	philo->id_philo = id;
	table->fork[id] = 0;
	philo->fork_r = philo->id_philo;
	philo->fork_l = find_post(philo->id_philo, table->info->n_philo);
	philo->n_eat = 0;
	philo->fin = 0;
	philo->table = table;
	philo->t_last_eat = table->t_start;
}
