/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/14 18:25:17 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutex(t_table *table, int i)
{
	int	j;

	j = 0;
	if (i == 1)
	{
		while (j < table->philo_nbr)
		{
			pthread_mutex_destroy(&table->forks[j]);
			j++;
		}
	}
	usleep(1000000);
	pthread_mutex_destroy(&table->counter_mutex);
	pthread_mutex_destroy(&table->meals_mutex);
	pthread_mutex_destroy(&table->write);
	free(table->philo);
	free(table->forks);
	free(table);
	return (0);
}

void	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->table->write);
	printf("%ld %d %s", gettime() - philo->table->start, philo->id, str);
	pthread_mutex_unlock(&philo->table->write);
}

void	ft_sleep(int duration)
{
	long	time_start;

	time_start = gettime();
	while (gettime() - time_start < duration)
	{
		usleep(100);
	}
}

void	count_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->counter_mutex);
	philo->meals_counter += 1;
	pthread_mutex_unlock(&philo->table->counter_mutex);
}

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->counter_mutex);
	if (philo->meals_counter >= philo->table->max_meals
		&& philo->table->max_meals != -1)
		return (1);
	pthread_mutex_unlock(&philo->table->counter_mutex);
	return (0);
}
