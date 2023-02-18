/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sniffer_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:06:51 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/18 18:26:33 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int check_time_die(t_table *table)
{
	(void)table;
	return (1);
}

void sniffer_philo(t_table *table)
{
	int	i;
	int	end;

	end = 1;
	printf("Hola");
	while (end)
	{
		i = -1;
		while (table->info->n_philo > ++i)
		{
			if (check_time_die(table) != 1)
			{
				end = 0;
				break ;
			}
		}
	}
}
