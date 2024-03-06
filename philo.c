/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/04 15:37:43 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int arc, char **arv)
{
    t_table table;
    if (check_errors(arc, arv) == 0)
        printf("not good\n");
    else 
        printf("good\n");
    initialiser_philo(&table, arv);
}