/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 17:08:36 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/22 00:06:21 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].start = gettime();
		table->philos[i].time_last_meal = gettime();
		table->philos[i].left_fork = &table->forks[(i + 1)
			% (table->philo_nbr)];
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].table = table;
		i++;
	}
}

int	handele_philos(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->count, NULL);
	pthread_mutex_init(&table->lock_time, NULL);
	philo_init(table);
	while (i++ < table->philo_nbr)
		pthread_mutex_init(&table->forks[i], NULL);
	if (table->max_meals == 0)
	{
		printf("no meals\n");
		return (0);
	}
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_create(&table->philos[i].thread, NULL, routine,
			&table->philos[i]);
		i++;
	}
	return (1);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->philo_nbr == 1)
		one_philo(philo);
	if (philo->id % 2 == 0)
		ft_sleep(100);
	while (1)
	{
		pthread_mutex_lock(philo->left_fork);
		print(philo, gettime(), "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print(philo, gettime(), "has taken a fork");
		print(philo, gettime(), "is eating");
		pthread_mutex_lock(&philo->table->lock_time);
		philo->time_last_meal = gettime();
		pthread_mutex_unlock(&philo->table->lock_time);
		ft_sleep(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		count_meals(philo);
		print(philo, gettime(), "is sleeping");
		ft_sleep(philo->table->time_to_sleep);
		print(philo, gettime(), "is thinking");
	}
}

int	check_death(t_table *table)
{
	int		i;
	long	time;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&table->count);
		if (table->philos[i].meals_counter > table->max_meals
			&& table->max_meals != -1)
			return (0);
		pthread_mutex_unlock(&table->count);
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->lock_time);
			time = gettime() - table->philos[i].time_last_meal;
			if (time > table->time_to_die)
			{
				pthread_mutex_lock(&table->write);
				printf("%ld %d is dead\n", time, table->philos[i].id);
				return (0);
			}
			pthread_mutex_unlock(&table->lock_time);
			i++;
		}
	}
}
