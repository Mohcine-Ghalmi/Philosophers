/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:02:58 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/18 19:54:12 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_start_data(t_philosopher *philosopher, t_fork **forks
		, t_shared *shared, int n_philosopher)
{
	philosopher->shared = shared;
	philosopher->number = n_philosopher + 1;
	philosopher->last_eat = 0;
	philosopher->eating_number = 0;
	philosopher->right_f = &((*forks)[n_philosopher]);
	philosopher->right_taken = 0;
	philosopher->left_taken = 0;
	if (n_philosopher == shared->num - 1)
		philosopher->left_f = &((*forks)[0]);
	else
		philosopher->left_f = &((*forks)[n_philosopher + 1]);
	philosopher->left_f->fork_used = 0;
	pthread_mutex_init(&(philosopher->last_eat_locker), NULL);
	pthread_mutex_init(&(philosopher->left_f->lock), NULL);
	pthread_mutex_init(&(philosopher->eating_num_lock), NULL);
}

int	alloc_philos(t_philosopher **philosopheros, t_fork **forks
		, t_shared	*shared)
{
	int	n_philosopher;

	*philosopheros = malloc(sizeof(t_philosopher) * shared->num);
	if (!(*philosopheros))
		return (0);
	*forks = malloc(sizeof(t_fork) * shared->num);
	if (!(*forks))
	{
		free(*philosopheros);
		return (0);
	}
	n_philosopher = 0;
	while (n_philosopher < shared->num)
	{
		philo_start_data(&(*philosopheros)[n_philosopher],
			forks, shared, n_philosopher);
		n_philosopher++;
	}
	return (1);
}

int	init_shared(t_shared *shared, int argc, char **argv)
{
	if (argc < 5)
		return (0);
	shared->num = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->time_to_eat = ft_atoi(argv[3]);
	shared->time_to_sleep = ft_atoi(argv[4]);
	shared->number_of_eating = -1;
	if (argc > 5)
	{
		shared->number_of_eating = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) <= 0)
			return (0);
	}
	shared->is_dead = 0;
	pthread_mutex_init(&(shared->print_locker), NULL);
	pthread_mutex_init(&(shared->dead_locker), NULL);
	return (1);
}

int	check_args(t_shared *philosopherosophers)
{
	if (philosopherosophers->time_to_die >= 60
		&& philosopherosophers->time_to_die <= MAX_VALUE)
		if (philosopherosophers->time_to_eat >= 60
			&& philosopherosophers->time_to_eat <= MAX_VALUE)
			if (philosopherosophers->time_to_sleep >= 60
				&& philosopherosophers->time_to_sleep <= MAX_VALUE)
				return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_shared			shared;
	t_philosopher		*philosopheros;
	t_fork				*forks;

	if (!init_shared(&shared, argc, argv) || check_args(&shared))
		return (0);
	if (alloc_philos(&philosopheros, &forks, &shared) == 0)
		return (0);
	if (start_threads(&philosopheros, &shared) == 0)
		kill_philos(&philosopheros[0]);
	(void)pthread_join(shared.thread_checker, NULL);
	(void)thread_join(&philosopheros, &shared);
	(void)pthread_mutex_destroy(&shared.dead_locker);
	pthread_mutex_destroy(&shared.print_locker);
	free(philosopheros);
	free(forks);
	return (0);
}
