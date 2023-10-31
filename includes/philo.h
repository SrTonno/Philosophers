/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:08:36 by tvillare          #+#    #+#             */
/*   Updated: 2023/10/30 15:42:37 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>

# include "struct.h"

# define TEXT_FORK "has taken a fork"
# define TEXT_DINNER "is eating"
# define TEXT_SLEEP "is sleeping"
# define TEXT_THINK "is thinking"
# define TEXT_DIED "is died"
# define ERR_NUMBER "ERROR:\n Invalid number format. Please try again."
# define ERR_PARAM "ERROR: Function requires 5 or 6 parameters only."
# define PROTO_FUNC "./philo <philo> <die> <eat> <sleep> [<times eats>]"
# define NOT_EAT 0
# define TRUE 1
# define FALSE 0

///Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
t_info	*check_input(char **data, int count);
long	time_to_milis(struct timeval t_start, struct timeval t_end);
void	*ft_calloc(size_t count, size_t size);
void	milisleep(int max, t_table *table);
void	status_time(t_philo *philo, t_table *table, char *status, size_t time);
void	free_struct(t_table *table);
int		find_post(int id, int max);
void	set_info_philo(t_philo *philo, t_table *table, int id);
///Philo
void	*thread_philo(void *data);
void	*sniffer_philo(void *table);
void	destroy_philo(t_table *table);

//Aciones
void	get_fork(t_table *table, t_philo *philo);
void	dinner(t_table *table, t_philo *philo);
void	leave_fork(t_table *table, t_philo *philo);

size_t	get_time(void);
void	mutex_print(char *status, t_philo *philo, t_table *table, int is_died);

#endif
