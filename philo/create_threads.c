/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:29:52 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/17 12:31:44 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	detach_fork(char *fork_name, t_philosopher *philosopher)
{
	int		*taken;
	t_fork	*fork;

	taken = &(philosopher->right_taken);
	fork = philosopher->right_f;
	if (ft_strncmp(fork_name, "left", 5) == 0)
	{
		taken = &(philosopher->left_taken);
		fork = philosopher->left_f;
	}
	pthread_mutex_lock(&(fork->lock));
	*taken = 0;
	fork->fork_used = 0;
	pthread_mutex_unlock(&(fork->lock));
}

void	detach_and_sleep(t_philosopher *philosopher)
{
	detach_fork("right", philosopher);
	detach_fork("left", philosopher);
	my_printer("is sleeping", philosopher);
	upgraded_usleep(philosopher->shared->time_to_sleep);
}

int	start_threads(t_philosopher **philosopheros, t_shared *shared)
{
	int	n_ph;

	shared->start_time = timevalue();
	n_ph = 0;
	while (n_ph < shared->num)
	{
		if (pthread_create(&((*philosopheros)[n_ph].thread), NULL,
			live_die, &((*philosopheros)[n_ph])) != 0)
			return (0);
		n_ph++;
	}
	if (pthread_create(&(shared->thread_checker), NULL,
			shinigami, philosopheros) != 0)
		return (0);
	return (1);
}

int	thread_join(t_philosopher **philosopheros, t_shared *shared)
{
	int	n_ph;

	n_ph = 0;
	while (n_ph < shared->num)
	{
		if (pthread_join((*philosopheros)[n_ph].thread, NULL))
			return (0);
		n_ph++;
	}
	n_ph = 0;
	while (n_ph < shared->num)
	{
		pthread_mutex_destroy(&(*philosopheros)[n_ph].left_f->lock);
		pthread_mutex_destroy(&(*philosopheros)[n_ph].right_f->lock);
		pthread_mutex_destroy(&(*philosopheros)[n_ph].last_eat_locker);
		n_ph++;
	}
	return (1);
}

void	*live_die(void *arg)
{
	t_philosopher		*philosopher;

	philosopher = (t_philosopher *)arg;
	if (philosopher->number % 2 != 0)
		upgraded_usleep(philosopher->shared->time_to_eat);
	while (!end_philo(philosopher))
	{
		if (philosopher->eating_number >= philosopher->shared->number_of_eating
			&& philosopher->shared->number_of_eating > 0)
			break ;
		fork_taker("left", philosopher);
		if (philosopher->left_taken)
			fork_taker("right", philosopher);
		if (philosopher->right_taken && philosopher->left_taken)
			after_taking(philosopher);
	}
	return (NULL);
}
