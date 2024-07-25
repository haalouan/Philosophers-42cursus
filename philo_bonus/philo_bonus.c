/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:21:24 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/24 12:54:40 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int arc, char **arv)
{
	t_philo	*philo;

	if (check_errors(arc, arv) == 0)
	{
		printf("ERORR IN ARGS\n");
		return (0);
	}
	philo = init_table(arc, arv);
	if (!philo)
		exit(1);
	init_process(philo);
	exit(0);
}
