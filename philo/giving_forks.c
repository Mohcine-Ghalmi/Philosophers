/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   giving_forks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:29:57 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/16 19:17:40 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	end_philo(t_philosopher *philosopher)
{
	int	alive;

	pthread_mutex_lock(&(philosopher->shared->dead_locker));
	alive = philosopher->shared->is_dead;
	pthread_mutex_unlock(&(philosopher->shared->dead_locker));
	return (alive);
}

int	kill_philos(t_philosopher *philosopher)
{
	pthread_mutex_lock(&(philosopher->shared->dead_locker));
	philosopher->shared->is_dead = 1;
	pthread_mutex_unlock(&(philosopher->shared->dead_locker));
	return (EXIT_FAILURE);
}

int	check_deth(t_philosopher *philosopher, long cur_time)
{
	int	dead;
	int	last_eat;

	dead = 0;
	pthread_mutex_lock(&(philosopher->last_eat_locker));
	last_eat = cur_time - philosopher->last_eat;
	pthread_mutex_unlock(&(philosopher->last_eat_locker));
	if (last_eat > philosopher->shared->time_to_die)
	{
		pthread_mutex_lock(&(philosopher->shared->print_locker));
		pthread_mutex_lock(&(philosopher->shared->dead_locker));
		philosopher->shared->is_dead = 1;
		pthread_mutex_unlock(&(philosopher->shared->dead_locker));
		// if(philosopher->eating_number < philosopher->shared->number_of_eating)
			printf("%ld %d died\n", cur_time, philosopher->number);
		pthread_mutex_unlock(&(philosopher->shared->print_locker));
		dead = 1;
	}
	return (dead);
}

void	*shinigami(void *arg)
{
	t_shared			*shared;
	t_philosopher		**philosopheros;
	long				cur_time;
	int					cur;

	philosopheros = (t_philosopher **)arg;
	shared = philosopheros[0]->shared;
	while (1)
	{
		cur = 0;
		cur_time = timevalue() - shared->start_time;
		while (cur < shared->num)
		{
			if (check_deth(&(*philosopheros)[cur], cur_time))
				return (NULL);
			cur++;
		}
		upgraded_usleep(1);
	}
	return (NULL);
}

void	fork_taker(char *fork_name, t_philosopher *philosopher)
{
	int		*taken;
	t_fork	*fork;

	if (!end_philo(philosopher))
	{
		taken = &(philosopher->right_taken);
		fork = philosopher->right_f;
		if (ft_strncmp(fork_name, "left", 5) == 0)
		{
			taken = &(philosopher->left_taken);
			fork = philosopher->left_f;
		}
		pthread_mutex_lock(&(fork->lock));
		if (!(*taken) && !fork->fork_used)
		{
			*taken = 1;
			fork->fork_used = 1;
			pthread_mutex_unlock(&(fork->lock));
			my_printer("has taken a fork", philosopher);
		}
		else
			pthread_mutex_unlock(&(fork->lock));
	}
}
