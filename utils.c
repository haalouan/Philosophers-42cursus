/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/24 22:11:58 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_table *table) //ok
{
	int i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].meals_counter = 0;
		table->start = gettime();
		table->philos[i].time_last_meal = gettime();
		table->philos[i].table = table;
		table->philos[i].left_fork = table->forks[i];
		table->philos[i].right_fork = table->forks[(i + 1) % table->philo_nbr];
		// if (table->philos[i].id % 2 == 0)
		// {
		// 	table->philos[i].right_fork = table->forks[i];
		// 	table->philos[i].left_fork = table->forks[(i + 1) % table->philo_nbr];
		// }
		i++;
	}
}


long gettime()
{ 
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}




int check_death(t_table *table)
{
	int i;

	while (1)
	{
		i = 0;
		if (table->philos[i].meals_counter > table->max_meals && table->max_meals != -1)
			exit(0);
		while (i < table->philo_nbr)
		{
			if (gettime() -  table->philos[i].time_last_meal > table->time_to_die)
			{
				printf("%ld  %d is dead\n", gettime() - table->start, table->philos[i].id);
				exit(0);
			}
			i++;
		}
	}
}

void ft_sleep(long time)
{
	long start = gettime();
	while (gettime() - start < time)
	{
		usleep(10);
	}
}

void *dinner_simmulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_sleep(400);
	while (1)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("%ld  %d has taking a fork\n", gettime() - philo->table->start, philo->id);
		printf("%ld  %d has taking a fork\n",  gettime() - philo->table->start, philo->id);
		printf("%ld  %d is eating\n",  gettime() - philo->table->start, philo->id);
		philo->time_last_meal = gettime();
		if (philo->table->max_meals != -1)
			philo->meals_counter++;
		ft_sleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);
		printf("%ld  %d is sleeping\n",  gettime() - philo->table->start,  philo->id);
		ft_sleep(philo->table->time_to_sleep);
		printf("%ld  %d is thinking\n",  gettime() - philo->table->start,  philo->id);
	}
	exit (0);
}

void initialiser_philo(t_table *table, char **arv)
{
	if (!table->philo_nbr)
		exit(0);
	int i =  0;
	philo_init(table);
	while (i++ < table->philo_nbr)
		pthread_mutex_init(&table->forks[i], NULL);
	if (table->max_meals == 0)
		exit(0);
	else if (table->philo_nbr == 1)
		one_philo();
	else
	{
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_create(&table->philos[i].thread, NULL, dinner_simmulation, &table->philos[i]);
			i++;
		}
	}
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
void one_philo()
{
	printf("one philo\n");
	
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s != '\0')
		{
			ft_putchar_fd(*s, fd);
			s++;
		}
	}
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd >= 0)
	{
		write(fd, &c, 1);
	}
}