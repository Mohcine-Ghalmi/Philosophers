/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:04:31 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/16 19:11:56 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	kill_proce(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;

	n_philo = 0;
	while (n_philo < shared->num)
		kill((*philos)[n_philo++].pid, SIGTERM);
	return (1);
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
		if (time - phil->last_meal > phil->shared->time_to_die)
		{
			sem_wait(phil->shared->printer);
			if (phil->eating_count < phil->shared->eating_number)
				printf("%d %d died\n", time, phil->pos);
			sem_post(phil->shared->finished);
			exit(1);
		}
		upgraded_usleep(1);
	}
	return (NULL);
}

void	*wait_death(void *arg)
{
	t_philosopher		**philos;
	t_shared			*shared;

	philos = (t_philosopher **)arg;
	shared = philos[0]->shared;
	sem_wait(shared->finished);
	kill_proce(philos, shared);
	return (NULL);
}

