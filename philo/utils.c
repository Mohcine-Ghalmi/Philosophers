/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:15:13 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/17 14:55:22 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	after_taking(t_philosopher *philosopher)
{
	my_printer("is eating", philosopher);
	upgraded_usleep(philosopher->shared->time_to_eat);
	pthread_mutex_lock(&philosopher->eating_num_lock);
	philosopher->eating_number++;
	pthread_mutex_unlock(&philosopher->eating_num_lock);
	pthread_mutex_lock(&(philosopher->last_eat_locker));
	philosopher->last_eat = timevalue()
		- philosopher->shared->start_time;
	pthread_mutex_unlock(&(philosopher->last_eat_locker));
	detach_and_sleep(philosopher);
	my_printer("is thinking", philosopher);
}

void	checking_eating(t_philosopher *philosopher, int *dead)
{
	pthread_mutex_lock(&philosopher->eating_num_lock);
	if (philosopher->eating_number >= philosopher->shared->number_of_eating)
	{
		pthread_mutex_unlock(&philosopher->eating_num_lock);
		*dead = 1;
	}
	pthread_mutex_unlock(&philosopher->eating_num_lock);
}
