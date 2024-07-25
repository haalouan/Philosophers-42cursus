/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:05:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/24 19:34:17 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				nbr_meals;
	int				meals_counter;
	long			time_last_meal;
	long			start;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	int				philo_nbr;
	int				max_meals;
	long			time_to_eat;
	long			time_to_die;
	long			time_to_sleep;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	count;
	pthread_mutex_t	lock_time;
}					t_table;

int		check_errors(int arc, char **arv);
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		handele_philos(t_table *table);
int		check_death(t_table *table);
int		check_errors(int arc, char **arv);
void	*routine(void *data);
void	ft_sleep(long time);
void	print(t_philo *philo, long time, char *WRITE);
void	one_philo(t_philo *philo);
void	count_meals(t_philo *philo);
long	gettime(void);

#endif