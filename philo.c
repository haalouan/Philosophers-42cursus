/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/21 02:29:31 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int arc, char **arv)
{
    t_table *table = malloc(sizeof(t_table));
    table->philos = malloc(sizeof(t_philo) * ft_atoi(arv[1]));
    table->forks = malloc(ft_atoi(arv[1]));
    // if (check_errors(arc, arv) == 0)
    // {
    //     printf("not good\n");
    //     exit(0);
    // }
    // else if (check_errors(arc, arv) == 1)
    //     printf("good\n");
    table->philo_nbr = ft_atoi(arv[1]);
    table->time_to_die = ft_atoi(arv[2]);
	table->time_to_eat = ft_atoi(arv[3]);
	table->time_to_sleep = ft_atoi(arv[4]);
	table->nbr_limit_meals = ft_atoi(arv[5]);
    initialiser_philo(table, arv);
}
