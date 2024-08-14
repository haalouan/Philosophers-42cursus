/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:23 by haalouan          #+#    #+#             */
/*   Updated: 2024/08/14 10:12:03 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	if (check_errors(ac, av) == 0)
	{
		printf("ERORR IN ARGS\n");
		return (0);
	}
	if (init_malloc(&table, av, ac))
		return (1);
	if (handle_philos(table) == 1)
	{
		destroy_mutex(table, 1);
		return (1);
	}
	destroy_mutex(table, 1);
	return (0);
}
