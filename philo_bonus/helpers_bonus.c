/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:22:47 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:43:57 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, long time, char *WRITE)
{
	sem_wait(philo->print);
	printf("%ld %ld %s\n", time - philo->start, philo->philo_nbr, WRITE);
	sem_post(philo->print);
}

void	ft_usleep(long time)
{
	long	start;

	start = gettime();
	while (gettime() - start < time)
	{
		usleep(100);
	}
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
