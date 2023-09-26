/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 16:45:36 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/26 19:13:14 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_number(char *str)
{
	int	index;

	index = -1;
	while (str[++index] != '\0')
	{
		if ((str[index] < '0' || str[index] > '9')
			&& (str[index] == '+' && index > 0))
			return (-1);
	}
	return (ft_atoi(str));
}

static t_info	*save_info(char **data, int count)
{
	t_info	*info;

	info = malloc(1 * sizeof(t_info));
	info->n_philo = check_number(data[1]);
	info->t_die = check_number(data[2]);
	info->t_eat = check_number(data[3]);
	info->t_sleep = check_number(data[4]);
	if (count == 6)
	{
		info->max_eat = check_number(data[5]);
		info->has_max_eat = TRUE;
	}
	else
	{
		info->max_eat = NOT_EAT;
		info->has_max_eat = FALSE;
	}
	return (info);
}

t_info	*check_input(char **data, int count)
{
	t_info	*info;

	if (count != 5 && count != 6)
	{
		printf("%s\n %s\n", ERR_PARAM, PROTO_FUNC);
		return (NULL);
	}
	info = save_info(data, count);
	if (info->n_philo <= 0 || info->t_die <= 0 || info->t_eat <= 0
		|| info->t_sleep <= 0 || \
		(info->max_eat <= 0 && info->has_max_eat == TRUE))
	{
		free(info);
		info = NULL;
		printf("%s\n %s\n", ERR_NUMBER, PROTO_FUNC);
	}
	return (info);
}
