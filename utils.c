/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:09:48 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/06 17:44:39 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	give_mutex(t_philo *philosopher, pthread_mutex_t *eat
		, pthread_mutex_t *n_eat, pthread_mutex_t *death)
{
	philosopher->shared->time_start = timevalue();
	philosopher->l_eat = eat;
	philosopher->num_eating = n_eat;
	philosopher->death_print = death;
}

void	fr(pthread_mutex_t *eat, pthread_mutex_t *n_eat, pthread_mutex_t *death)
{
	free(death);
	free(n_eat);
	free(eat);
}

int	philo_data_testing_alloc(t_philo **philosopher
		, long number_of_philosophers, char **argv)
{
	int	n;

	n = 0;
	while (n < number_of_philosophers)
	{
		philosopher[n] = malloc(sizeof(t_philo));
		pthread_mutex_init(&philosopher[n]->right_fork, NULL);
		philosopher[n]->shared = malloc(sizeof(t_shared));
		if (data_taking(philosopher[n]->shared, argv))
		{
			free(philosopher[0]);
			free(philosopher[0]->shared);
			free(philosopher);
			printf("\033[31minvalid arguments");
			return (0);
		}
		++n;
	}
	return (1);
}

void	fr2(t_philo **philosopher, long number_of_philosophers)
{
	int	n;

	n = 0;
	while (n < number_of_philosophers)
	{
		free(philosopher[n]->shared);
		free(philosopher[n++]);
	}
	free(philosopher);
}
