/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:05:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/21 03:20:24 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>



typedef struct s_philo
{
    int         id;
    long        nbr_meals;
    long        max_meals;
    int full;
    long        time_last_meal;
    pthread_mutex_t     left_fork;
    pthread_mutex_t       right_fork;  // dyalo
    pthread_t   thread; //thread
    int meals_counter;
    struct s_table    *table;
    int is_dead;
}               t_philo;

typedef struct s_table
{
    long    philo_nbr;
    //
    long    time_to_eat;
    long    time_to_die;
    long    time_to_sleep;
    long    nbr_limit_meals;
    //
    pthread_mutex_t *fork;
    int     all_thread_ready;
    long    start;
    long    end;
    pthread_mutex_t   *forks;//array forks
    t_philo *philos; //array
}t_table;



int     check_errors(int arc, char **arv);
int     ft_strlen(const char *str);
int     ft_atoi(const char *str);
void    initialiser_philo(t_table *table, char **arv);
void	ft_putstr_fd(char *s, int fd);
int check_errors(int arc, char **arv);
void	ft_putchar_fd(char c, int fd);
void *dinner_simmulation(void *data);
void one_philo();
int check_end(t_philo *philo);
#endif