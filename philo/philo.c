/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/06/27 12:33:40 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_ready(t_table *table)
{
	if (table->philo_nbr == 0)
	{
		printf("no philos\n");
		return (0);
	}
	if (table->time_to_die == 0 || table->time_to_eat == 0
		|| table->time_to_sleep == 0)
	{
		printf("Error in ARGS\n");
		return (0);
	}
	return (1);
}

int	main(int arc, char **arv)
{
	t_table	*table;

	if (check_errors(arc, arv) == 0)
	{
		printf("ERORR IN ARGS\n");
		return (0);
	}
	table = malloc(sizeof(t_table));
	table->philos = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
	table->forks = malloc(ft_atoi(arv[1]));
	table->philo_nbr = ft_atoi(arv[1]);
	table->time_to_die = ft_atoi(arv[2]);
	table->time_to_eat = ft_atoi(arv[3]);
	table->time_to_sleep = ft_atoi(arv[4]);
	if (arv[5] != NULL)
		table->max_meals = ft_atoi(arv[5]);
	else
		table->max_meals = -1;
	if (get_ready(table) == 0)
		return (0);
	if (handele_philos(table) == 0)
		return (0);
	if (check_death(table) == 0)
		return (0);
}
