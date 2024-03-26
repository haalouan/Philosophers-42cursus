/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:05:11 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/25 22:39:10 by haalouan         ###   ########.fr       */
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
    int             id;
    long            nbr_meals;
    int             meals_counter;
    long            time_last_meal;
    pthread_mutex_t left_fork; //dyal sahbo
    pthread_mutex_t right_fork;  // dyalo
    pthread_t       thread; //thread
    struct s_table  *table;
    long            start;
}               t_philo;

typedef struct s_table
{
    long            philo_nbr;
    //
    long            time_to_eat;
    long            time_to_die;
    long            time_to_sleep;
    long            max_meals;
    //
    long            end;
    pthread_mutex_t *forks;//array forks
    t_philo         *philos; //array
    pthread_mutex_t write;
    pthread_mutex_t count;
    pthread_mutex_t lock;
}t_table;



int     check_errors(int arc, char **arv);
int     ft_strlen(const char *str);
int     ft_atoi(const char *str);
int     handele_philos(t_table *table);
void	ft_putstr_fd(char *s, int fd);
int     check_errors(int arc, char **arv);
void	ft_putchar_fd(char c, int fd);
void    *dinner_simmulation(void *data);
int     check_death(t_table *table);
long    gettime();
void    ft_sleep(long time);
#endif