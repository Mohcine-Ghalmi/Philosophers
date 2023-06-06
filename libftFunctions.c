/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftFunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:06:51 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/06 17:47:45 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	res;
	long	i;
	int		signe;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		signe *= -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (-1);
		else
			res = res * 10 + (str[i] - '0');
		i++;
	}
	return (signe * res);
}

void	my_usleep(long milis)
{
	long int	timev;

	timev = timevalue();
	while (timevalue() - timev < milis)
		usleep(milis / 10);
}

int	check_args(t_shared *philosophers)
{
	if (philosophers->time_to_die >= 60
		&& philosophers->time_to_die <= MAX_VALUE)
		if (philosophers->time_to_eat >= 60
			&& philosophers->time_to_eat <= MAX_VALUE)
			if (philosophers->time_to_sleep >= 60
				&& philosophers->time_to_sleep <= MAX_VALUE)
				return (0);
	return (1);
}

int	data_taking(t_shared *philosophers, char **argv)
{
	philosophers->time_to_die = ft_atoi(argv[2]);
	philosophers->time_to_eat = ft_atoi(argv[3]);
	philosophers->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		philosophers->number_of_times_each_philosopher_must_eat
			= ft_atoi(argv[5]);
		if (philosophers->number_of_times_each_philosopher_must_eat < 0)
			return (1);
	}
	else
		philosophers->number_of_times_each_philosopher_must_eat
			= -1;
	return (check_args(philosophers));
}

void	create_philosophers(t_philo **philosopher, long number_of_philosophers)
{
	int	n_ph;

	n_ph = 0;
	while (n_ph < number_of_philosophers)
	{
		philosopher[n_ph]->number = n_ph + 1;
		philosopher[n_ph]->last_eat = 0;
		if (n_ph == number_of_philosophers - 1)
			philosopher[n_ph]->left_fork = &(philosopher[0]->right_fork);
		else
			philosopher[n_ph]->left_fork = &(philosopher[n_ph + 1]->right_fork);
		n_ph++;
	}
}
