/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvil	lare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:52:29 by tvillare          #+#    #+#             */
/*   Updated: 2023/01/13 18:13:55 by tvillare         ###   ########.fr       */
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

///Utils
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
t_info	*check_input(char **data, int count);
long	time_to_milis(struct timeval t_start, struct timeval t_end);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	milisleep(int max, t_table *table);
void	status_time(t_philo *philo, t_table *table, char *status, int time);
///Philo
void	*thread_philo(void *data);
void	*sniffer_philo(void *table);

//Aciones
void	get_fork(t_table *table, t_philo *philo, int post);
void	dinner(t_table *table, t_philo *philo, int post);
void	leave_fork(t_table *table, t_philo *philo, int post);


#endif
