/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/11 12:20:25 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	main(int ac, char **av)
{
	t_table	*table;

	if (check_errors(ac, av) == 0)
	{
		printf("ERORR IN ARGS\n");
		return (0);
	}
	if (init_malloc(&table, av, ac))
		return (1);
	if (handle_philos(table) == 1)
	{
		destroy_mutex(table, 1);
		return (1);
	}
	destroy_mutex(table, 1);
	return (0);
}
