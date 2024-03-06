/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:05:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/04 15:38:06 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>//
#include <sys/time.h>//
#include <limits.h>

typedef struct s_table t_table;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
}                   t_fork;

typedef struct s_philo
{
    int         id;
    long        nbr_meals;
    long        max_meals;
    long        time_last_meal;
    t_fork      *left_fork;
    t_fork      *right_fork;
    pthread_t   thread_nbr;
    //t_table     table;
}               t_philo;

struct s_table
{
    long    philo_nbr;
    long    time_to_eat;
    long    time_to_die;
    long    time_to_sleep;
    long    nbr_limit_meals;
    long    start_simulation;
    long    end_simulation;
    t_fork  *fork;
    t_philo *philos;
};

int     check_errors(int arc, char **arv);
int     ft_strlen(const char *str);
int     ft_atoi(const char *str);
void    initialiser_philo(t_table *table, char **arv);

#endif