/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 14:23:48 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/11 16:09:17 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->write, NULL) != 0)
	{
		printf("pthread_mutex_init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&table->meals_mutex, NULL) != 0)
	{
		printf("pthread_mutex_init failed\n");
		return (1);
	}
	if (pthread_mutex_init(&table->counter_mutex, NULL) != 0)
	{
		printf("pthread_mutex_init failed\n");
		return (1);
	}
	init_forks(table);
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			printf("pthread_mutex_init failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_philo(t_table **table, char **av, int ac)
{
	(*table)->philo_nbr = ft_atoi(av[1]);
	(*table)->time_to_die = ft_atoi(av[2]);
	(*table)->time_to_eat = ft_atoi(av[3]);
	(*table)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*table)->max_meals = ft_atoi(av[5]);
	else
		(*table)->max_meals = -1;
	(*table)->start = gettime();
}

int	init_malloc(t_table **table, char **av, int ac)
{
	if (ft_atoi(av[1]) == 0)
	{
		printf("ERROR IN ARGS\n");
		return (1);
	}
	*table = (t_table *)malloc(sizeof(t_table));
	if (!(*table))
		return (printf("Malloc failed\n"));
	(*table)->philo = (t_philo *)malloc(sizeof(t_philo)
			* ft_atoi(av[1]));
	if (!(*table)->philo)
	{
		free((*table));
		return (printf("Malloc failed\n"));
	}
	(*table)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* ft_atoi(av[1]));
	if (!(*table)->forks)
	{
		free((*table)->philo);
		free((*table));
		return (printf("Malloc failed\n"));
	}
	init_philo(table, av, ac);
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		if (pthread_create(&table->philo[i].thread, NULL, routine,
				&table->philo[i]))
		{
			printf("pthread_create failed\n");
			return (1);
		}
		pthread_detach(table->philo[i].thread);
		i++;
	}
	if (check_death(table) == 1)
		return (1);
	return (0);
}
