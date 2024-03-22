/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/21 05:28:30 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_init(t_table *table) //ok
{
	int i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_dead = -1;
		table->philos[i].full = -1;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = table->forks[i];
		table->philos[i].right_fork = table->forks[(i + 1) % table->philo_nbr];
		if (table->philos[i].id % 2 == 0)
		{
			table->philos[i].right_fork = table->forks[i];
			table->philos[i].left_fork = table->forks[(i + 1) % table->philo_nbr];
		}
		i++;
	}
}

long gettime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
}

void *dinner_simmulation(void *data)
{
	t_philo *philo;
	philo = (t_philo *)data;
	// if (philo->id % 2 == 0)
	// 	usleep(500);
	if (philo->table == NULL)
		printf("NULL\n");
	//printf("ok\n");
	while (check_end(philo) == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("%ld philo n: %d has taking a fork\n", gettime(), philo->id);
		printf("%ld philo n: %d has taking a fork\n", gettime(), philo->id);
		printf("%ld philo n: %d is eating\n", gettime(), philo->id);
		// if (philo->meals_counter <= philo->table->nbr_limit_meals)
		// {
		// 	printf("max meals\n");
		// 	exit(0);
		// }
		if (philo->table->time_to_die <= philo->table->start - gettime())
		{
			printf("%ld / philo n: %d is dead\n", gettime(), philo->id);
			exit(0);
		}
		philo->meals_counter++;
		usleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(&philo->right_fork);

		printf("philo n: %d is sleeping\n", philo->id);
		usleep(philo->table->time_to_sleep);
		
		printf("philo n: %d is thinking\n", philo->id);
		
	}
	return philo;
}

void initialiser_philo(t_table *table, char **arv)
{
	if (!table->philo_nbr)
		exit(0);
	int i =  0;
	philo_init(table);
	while (i++ < table->philo_nbr)
	{
		pthread_mutex_init(&table->forks[i], NULL);
	}
	i = 0;
	table->start = gettime();
	if (table->nbr_limit_meals == 0)
		exit(0);
	else if (table->philo_nbr == 1)
		one_philo();
	else
	{
		i = 1;
		while (i < table->philo_nbr)//not ok
		{
			pthread_create(&table->philos[i].thread, NULL, dinner_simmulation, &table->philos[i]);
			i++;
		}
		i = 0;
		while (i < table->philo_nbr)
		{
			pthread_join(table->philos[i].thread, NULL);
			i++;
		}
	}
}






/**************************************/
int check_errors(int arc, char **arv)
{
    int i;
    int j;

    i = 1;
	j = 0;
    if (arc != 6)
        return (0);
    while (i < 6)
    {
        j = 0;
        while (arv[i][j] != '\0')
        {
            if ((arv[i][j] <= '0' || arv[i][j] >= '9') && arv[i][j] != '+')
                return (0);
            else 
				j++;
        }
        i++;
    }
    return (1);
}

int check_end(t_philo *philo)
{
	if (philo->table->time_to_die < philo->table->start - gettime())
	{
		printf("philo n: %d is dead\n", philo->id);
		exit(0);
		philo->is_dead = 1;
	}
	// if (philo->meals_counter >= philo->table->nbr_limit_meals)
	// {
	// 	printf("max meals\n");
	// 	exit(0);
	// }
	// if (philo->is_dead == 1)
	// 	return 1;
	return 0;
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