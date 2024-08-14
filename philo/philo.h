/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:05:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/14 09:26:30 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	long			meals_counter;
	long			last_eat;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	pthread_mutex_t	write;
	pthread_mutex_t	meals_mutex;
	pthread_mutex_t	counter_mutex;
	int				philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	long			start;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_table;

int		check_meals(t_philo *philo, int max_meals);
void	ft_sleep(int duration);
int		destroy_mutex(t_table *table, int i);
int		check_death(t_table *table);
int		ft_atoi(const char *str);
int		handle_philos(t_table *table);
void	*routine(void *arg);
long	gettime(void);
int		create_threads(t_table *table);
void	print(t_philo *philo, char *str);
int		check_errors(int arc, char **arv);
int		init_mutex(t_table *table);
int		init_forks(t_table *table);
void	count_meals(t_philo *philo);
void	init_philo(t_table **table, char **av, int ac);
int		init_malloc(t_table **table, char **av, int ac);
#endif
