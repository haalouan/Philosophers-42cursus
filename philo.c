/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/25 06:14:23 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//void f(){system("leaks philo");}

int main(int arc, char **arv)
{
    //atexit(f);
    if (check_errors(arc, arv) == 0)
    {
        ft_putstr_fd("ERROR IN ARGS\n", 2);
        return (0);
    }
    t_table *table = malloc(sizeof(t_table));
    table->philos = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
    table->forks = malloc(ft_atoi(arv[1]));
    table->philo_nbr = ft_atoi(arv[1]);
    if (table->philo_nbr == 0)
    {
        ft_putstr_fd("no philos\n", 1);
        return (0);
    }
    table->time_to_die = ft_atoi(arv[2]);
	table->time_to_eat = ft_atoi(arv[3]);
	table->time_to_sleep = ft_atoi(arv[4]);
    if (arv[5] != NULL)
	    table->max_meals = ft_atoi(arv[5]);
    else 
        table->max_meals = -1;
    if (handele_philos(table) == 0)
        return (0);
    if (check_death(table) == 0)
        return (0);
}
