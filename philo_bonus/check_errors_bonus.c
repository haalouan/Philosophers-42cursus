/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:22:21 by haalouan          #+#    #+#             */
/*   Updated: 2024/07/21 18:21:38 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_errors(int arc, char **arv)
{
	int	i;
	int	j;

	i = 1;
	if (arc != 5 && arc != 6)
		return (0);
	while (i < arc)
	{
		j = 0;
		while (arv[i][j] != '\0')
		{
			if (arv[i][j] < '0' || arv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				signe;
	int				count;

	i = 0;
	result = 0;
	signe = 1;
	count = 0;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	return (result * signe);
}
