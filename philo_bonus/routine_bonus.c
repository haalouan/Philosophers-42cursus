/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:23:06 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:43:57 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_philo *table)
{
	sem_unlink("print");
	sem_unlink("forks");
	table->print = sem_open("print", O_CREAT, 0644, 1);
	table->forks = sem_open("forks", O_CREAT, \
								0644, table->nb_forks);
	if (table->print <= 0 || table->forks <= 0)
	{
		ft_error("Error: semaphore open error");
		return (1);
	}
	return (0);
}

t_philo	*init_table(int arc, char **arv)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		exit (1);
	philo->pid = malloc(sizeof(int) * ft_atoi(arv[1]));
	if (!philo->pid)
		exit (1);
	philo->nb_philo = ft_atoi(arv[1]);
	philo->time_to_die = ft_atoi(arv[2]);
	philo->time_to_eat = ft_atoi(arv[3]);
	philo->time_to_sleep = ft_atoi(arv[4]);
	if (arc == 6)
		philo->max_meals = ft_atoi(arv[5]);
	else
		philo->max_meals = -1;
	if (philo->max_meals == 0)
		exit (1);
	philo->counter = 0;
	philo->stop = 0;
	philo->died = 0;
	philo->nb_forks = philo->nb_philo;
	if (init_semaphores(philo) == 1)
		return (NULL);
	return (philo);
}

int	init_process(t_philo *philo)
{
	int	i;

	i = -1;
	philo->start = gettime();
	while (++i < philo->nb_philo)
	{
		philo->pid[i] = fork();
		if (philo->pid[i] == -1)
			ft_error("Error in fork\n");
		if (philo->pid[i] == 0)
		{
			philo->philo_nbr = i + 1;
			philo->last_eat = gettime();
			routine(philo);
		}
	}
	exit_philo(philo);
	return (0);
}

void	exit_philo(t_philo *philo)
{
	int		i;
	int		status;

	i = 0;
	while (i < philo->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->nb_philo)
				kill(philo->pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	sem_close(philo->print);
	sem_close(philo->forks);
	sem_unlink("print");
	sem_unlink("forks");
	free(philo->pid);
	free(philo);
}

void	routine(t_philo *philo)
{
	if (pthread_create(&philo->check_monitor, \
			NULL, &check_death, philo))
		ft_error("Error: Failed to create the thread");
	while (1)
	{
		sem_wait(philo->forks);
		ft_print(philo, gettime(), "has taken a fork");
		sem_wait(philo->forks);
		ft_print(philo, gettime(), "has taken a fork");
		ft_print(philo, gettime(), "is eating");
		ft_usleep(philo->time_to_eat);
		philo->last_eat = gettime();
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->counter += 1;
		ft_print(philo, gettime(), "is sleeping");
		ft_usleep(philo->time_to_sleep);
		ft_print(philo, gettime(), "is thinking");
	}
}
