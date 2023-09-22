/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 12:32:34 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/22 12:42:42 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef STRUCT_H
# define STRUCT_H
#include "philo.h"

//https://www.delftstack.com/es/howto/c/gettimeofday-in-c/

typedef struct	s_philo
{
	int				id_philo;
	int				n_eat;
	size_t			t_last_eat;
	size_t			t_end;
	int				fork_r;
	int				fork_l;
}	t_philo;

typedef struct	s_info
{
	int	n_philo;
	int	t_die;
	int	t_sleep;
	int	t_eat;
	int	max_eat;
}	t_info;

typedef struct	s_table
{
	pthread_mutex_t	*mutex;
	int				id_tmp;
	pthread_mutex_t	prot_end;
	int				end;
	size_t			t_start;
	pthread_t		*philo;
	pthread_t		sniffer;
	t_info			*info;
	t_philo			*stats;
}	t_table;

#endif
