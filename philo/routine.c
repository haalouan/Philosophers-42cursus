/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:08:36 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/11 14:33:57 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_sleep(philo->table->time_to_eat / 2);
	while (check_meals(philo, philo->table->max_meals) != 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		print(philo, "has taken a fork\n");
		print(philo, "is eating\n");
		ft_sleep(philo->table->time_to_eat);
		pthread_mutex_lock(&philo->table->meals_mutex);
		philo->last_eat = gettime();
		pthread_mutex_unlock(&philo->table->meals_mutex);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		count_meals(philo);
		print(philo, "is sleeping\n");
		ft_sleep(philo->table->time_to_sleep);
		print(philo, "is thinking\n");
	}
	return (NULL);
}

int	check_death(t_table *table)
{
	int	i;

	while (1)
	{
		i = 0;
		if (check_meals(&table->philo[i], table->max_meals) == 1)
			return (1);
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->philo[i].table->meals_mutex);
			if (gettime() - table->philo[i].last_eat >= table->time_to_die)
			{
				pthread_mutex_lock(&table->philo[i].table->write);
				printf("%ld %d died\n", gettime() - table->philo[i].start,
					table->philo[i].id);
				return (1);
			}
			pthread_mutex_unlock(&table->philo[i].table->meals_mutex);
			i++;
		}
	}
	return (1);
}

int	handle_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philo[i].id = i + 1;
		table->philo[i].meals_counter = 0;
		table->philo[i].start = table->start;
		table->philo[i].last_eat = gettime();
		table->philo[i].right_fork = &table->forks[(i + 1) % table->philo_nbr];
		table->philo[i].left_fork = &table->forks[i];
		table->philo[i].table = table;
		i++;
	}
	if (init_mutex(table))
		return (1);
	if (create_threads(table) == 1)
		return (1);
	return (0);
}
