/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/26 01:54:20 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_table *table) 
{
	int i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->philos[i].start = gettime();
		table->philos[i].time_last_meal = gettime();
		table->philos[i].table = table;
		table->philos[i].left_fork = table->forks[i];
		table->philos[i].right_fork = table->forks[1];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].right_fork = table->forks[i];
			table->philos[i].left_fork = table->forks[(i + 1) % table->philo_nbr];
		}
		i++;
	}
}

int check_death(t_table *table)
{
	int i = 0;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&table->count);
		if (table->philos[i].meals_counter > table->max_meals && table->max_meals != -1)
			return 0;
		pthread_mutex_unlock(&table->count);
		while (i < table->philo_nbr)
		{
			pthread_mutex_lock(&table->lock);
			if (gettime() -  table->philos[i].time_last_meal > table->time_to_die)
			{
				pthread_mutex_lock(&table->write);
				printf("%ld  %d is dead\n", gettime() - table->philos[i].start, table->philos[i].id);
				return 0;
			}
			pthread_mutex_unlock(&table->lock);
			i++;
		}
	}
}

void *dinner_simmulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	if (philo->table->philo_nbr == 1)
	{
		printf("%ld  %d has taking a fork\n", gettime() - philo->start, philo->id);
		while(1){}
	}
	if (philo->id % 2 == 0)
		ft_sleep(200);
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		pthread_mutex_lock(&philo->table->write);
		printf("%ld  %d has taking a fork\n", gettime() - philo->start, philo->id);
		//pthread_mutex_unlock(&philo->table->write);
		
		//pthread_mutex_lock(&philo->right_fork);

		//pthread_mutex_lock(&philo->table->write);
		printf("%ld  %d has taking a fork\n",  gettime() - philo->start, philo->id);
		//pthread_mutex_unlock(&philo->table->write);
		
		//pthread_mutex_lock(&philo->table->write);
		printf("%ld  %d is eating\n",  gettime() - philo->start, philo->id);
		pthread_mutex_unlock(&philo->table->write);
		
		ft_sleep(philo->table->time_to_eat);
		
		pthread_mutex_lock(&philo->table->lock);
		philo->time_last_meal = gettime();
		pthread_mutex_unlock(&philo->table->lock);
		
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);

		pthread_mutex_lock(&philo->table->count);
		if (philo->table->max_meals != -1)
			philo->meals_counter++;
		pthread_mutex_unlock(&philo->table->count);
		
		pthread_mutex_lock(&philo->table->write);
		printf("%ld  %d is sleeping\n",  gettime() - philo->start,  philo->id);
		pthread_mutex_unlock(&philo->table->write);
		
		ft_sleep(philo->table->time_to_sleep);
	
		
		pthread_mutex_lock(&philo->table->write);
		printf("%ld  %d is thinking\n",  gettime() - philo->start,  philo->id);
		pthread_mutex_unlock(&philo->table->write);
	
	}
	exit (0);
}

int handele_philos(t_table *table)
{
	if (!table->philo_nbr)
		exit(0);
	int i =  0;
	philo_init(table);
	while (i < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->count, NULL);
	pthread_mutex_init(&table->lock, NULL);
	if (table->max_meals == 0)
	{
		printf("no meals\n");
		return (0);
	}
	else
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread, NULL, dinner_simmulation, &table->philos[i]);
			i++;
		}
	}
	return (1);
}

void ft_sleep(long time)
{
	long start = gettime();
	while (gettime() - start < time)
	{
		usleep(10);
	}
}

long gettime()
{ 
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


/**************************************/
int check_errors(int arc, char **arv)
{
	int i;
	int j;

	i  = 1;
    if (arc != 5 && arc != 6)
		return 0;
	while (i < arc)
	{
		j = 0;
		while (arv[i][j] != '\0')
		{
			if (arv[i][j] < '0' || arv[i][j] > '9')
				return 0;
			j++;
		}
		i++;
	}
    return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				signe;
	int				count;

	i = 0;
	result = 0;
	signe = 1;
	count = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * signe);
}
