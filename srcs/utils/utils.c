/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvillare <tvillare@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 11:17:27 by tvillare          #+#    #+#             */
/*   Updated: 2023/09/26 16:00:41 by tvillare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_to_milis(struct timeval t_start, struct timeval t_end)
{
	long	milis;

	milis = (((t_end.tv_sec - t_start.tv_sec) * 1000) + \
		((t_end.tv_usec - t_start.tv_usec) / 1000));
	return (milis);
}

int	ft_isdigit(int c)
{
	if (48 <= c && 57 >= c)
		return (1);
	else
		return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptn;
	size_t	len;
	size_t	i;

	i = 0;
	len = size * count;
	if (len && len / size != count)
		return (NULL);
	ptn = malloc(len);
	if (ptn == NULL)
		return (ptn);
	while (len > i)
		((char *)ptn)[i++] = '\0';
	return (ptn);
}

void	mutex_print(char *status, t_philo *philo, t_table *table, int is_died)
{
	(void)table;
	pthread_mutex_lock(&table->prot_print);
	if (table->end == 0 || is_died == TRUE)
		printf("%06ld %d %s\n", get_time() - table->t_start, \
			philo->id_philo + 1, status);
	pthread_mutex_unlock(&table->prot_print);
}
