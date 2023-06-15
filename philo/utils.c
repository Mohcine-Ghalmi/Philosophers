/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:15:13 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/15 16:15:26 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	after_taking(t_philosopher *philosopher)
{
	my_printer("is eating", philosopher);
	upgraded_usleep(philosopher->shared->time_to_eat);
	philosopher->eating_number++;
	pthread_mutex_lock(&(philosopher->last_eat_locker));
	philosopher->last_eat = timevalue()
		- philosopher->shared->start_time;
	pthread_mutex_unlock(&(philosopher->last_eat_locker));
	detach_and_sleep(philosopher);
	my_printer("is eating", philosopher);
	my_printer("is thinking", philosopher);
}
