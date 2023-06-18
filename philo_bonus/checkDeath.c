/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:04:31 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/19 00:29:24 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	kill_proce(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;

	n_philo = 0;
	if (waiting_philos(philos, shared) == 0)
		return (1);
	while (n_philo < shared->num)
		kill((*philos)[n_philo++].pid, SIGTERM);
	return (1);
}

void	printer_die(t_philosopher *phil, int time)
{
	sem_wait(phil->eating_num);
	sem_wait(phil->shared->printer);
	printf("%d %d died\n", time, phil->pos);
	sem_post(phil->shared->finished);
}

void	*end_philos(void *arg)
{
	t_philosopher		*phil;
	t_shared			*shared;
	int					time;

	phil = (t_philosopher *)arg;
	shared = phil->shared;
	while (1)
	{
		time = timevalue() - shared->start_time;
		sem_wait(phil->eating_num);
		if (shared->eating_number > 0
			&& phil->eating_count >= shared->eating_number)
		{
			sem_post(phil->eating_num);
			exit(0);
		}
		sem_post(phil->eating_num);
		if ((time - phil->last_meal) > phil->shared->time_to_die)
		{
			printer_die(phil, time);
			exit(1);
		}
		upgraded_usleep(10);
	}
	return (NULL);
}
