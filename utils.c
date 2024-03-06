/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:06:40 by haalouan          #+#    #+#             */
/*   Updated: 2024/03/04 20:53:12 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialiser_philo(t_table *table, char **arv)
{
    table->end_simulation = 0;
    table->philos = maloc(ft_atoi(arv[1]) * sizeof(t_philo));
	
}


int check_errors(int arc, char **arv)
{
    int i;
    int j;

    i = 0;
    if (arc != 6)
        return (0);
    while (arv[i] != NULL)
    {
        j = 0;
        while (arv[i][j] != '\0')
        {
            if (!((arv[i][j] >= '0' && arv[i][j] <= '9') || (arv[i][j] != '\0')))
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

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
