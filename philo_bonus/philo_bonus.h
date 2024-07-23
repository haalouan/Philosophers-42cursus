/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:20:22 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:43:57 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo
{
	int				*pid;
	long			counter;
	long			last_eat;
	long			stop;
	long			died;
	long			start;
	sem_t			*print;
	sem_t			*forks;
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_meals;
	long			nb_forks;
	long			philo_nbr;
	pthread_t		check_monitor;
}	t_philo;

int		check_errors(int arc, char **arv);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		check_errors(int arc, char **arv);
void	ft_usleep(long time);
long	gettime(void);
void	ft_print(t_philo *philo, long time, char *WRITE);
void	routine(t_philo *philo);
void	exit_philo(t_philo *tmp);
int		init_process(t_philo *philo);
t_philo	*init_table(int arc, char **arv);
int		init_semaphores(t_philo *table);
void	*check_death(void *args);
int		ft_error(char *str);

#endif