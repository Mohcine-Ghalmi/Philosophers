/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftFunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:51 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/04 16:52:47 by mghalmi          ###   ########.fr       */
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

int	my_usleep(long milis, t_philo *philosopher)
{
	long  int timev;

	timev = timevalue();
	while (timevalue() - timev < milis)
	{
		if (check_death(philosopher) == 0)
		{
			pthread_mutex_unlock(&(philosopher->right_fork));
    		pthread_mutex_unlock((philosopher->left_fork));
			return 0;
		}
		usleep(milis / 10);
	}
	return 1;
}

int check_args(t_shared *philosophers)
{
	if (philosophers->time_to_die >= 60 && philosophers->time_to_die <= max_value)
		if (philosophers->time_to_eat >= 60 && philosophers->time_to_eat <= max_value)
			if (philosophers->time_to_sleep >= 60 && philosophers->time_to_sleep <= max_value)
				return 0;
	return 1;
}

t_end *creat_end(pthread_mutex_t *end)
{
	t_end *new;

	new = malloc(sizeof(t_end));
	new->die = 0;
	new->death = end;
	return (new);
}