/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftFunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:51 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/11 17:12:48 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	res;
	long	i;
	int	signe;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (str[i] || signe == 0)
		return -1;
	return (signe * res);
}

int check_args(t_philo *philosophers)
{
	if (philosophers->number_of_philosophers > 0)
		if (philosophers->time_to_die >= 60 && philosophers->time_to_die <= max_value)
			if (philosophers->time_to_eat >= 60 && philosophers->time_to_eat <= max_value)
				if (philosophers->time_to_sleep >= 60 && philosophers->time_to_sleep <= max_value)
					return 0;
	return 1;
}
