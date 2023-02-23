/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:17:27 by tvillare          #+#    #+#             */
/*   Updated: 2023/02/23 11:23:57 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_to_milis(struct timeval t_start, struct timeval t_end)
{
	long milis;

	milis = (((t_end.tv_sec - t_start.tv_sec) * 1000) + \
		((t_end.tv_usec - t_start.tv_usec) / 1000));
	return (milis);
}
