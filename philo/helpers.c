/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:35:58 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:17:34 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(t_philo *philo, long time, char *WRITE)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d %s\n", time - philo->start, philo->id, WRITE);
	pthread_mutex_unlock(&philo->table->write);
}

void	one_philo(t_philo *philo)
{
	printf("%ld  %d has taken a fork\n", gettime() - philo->start, philo->id);
	while (1)
	{
	}
}

void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->count);
	if (philo->table->max_meals != -1)
		philo->meals_counter++;
	pthread_mutex_unlock(&philo->table->count);
}

void	ft_sleep(long time)
{
	long	start;

	start = gettime();
	while (gettime() - start < time)
	{
		usleep(10);
	}
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
