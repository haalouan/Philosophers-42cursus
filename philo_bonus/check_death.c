/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:22:48 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:43:57 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		if (gettime() - philo->last_eat > philo->time_to_die)
		{
			sem_wait(philo->print);
			printf("%ld %ld died\n", gettime() - philo->start, \
				philo->philo_nbr);
			exit (1);
		}
		if (philo->max_meals != -1 && philo->counter >= philo->max_meals)
			exit (0);
	}
	return (NULL);
}
