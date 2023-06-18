/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkDeath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:04:31 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/19 00:09:34 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	kill_proce(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;

	n_philo = 0;
	// sem_wait(shared->finished);
	if (waiting_philos(philos, shared) == 0)
		return (1);
	printf("after wait\n");
	while (n_philo < shared->num)
	{
		printf("index == %d\n", n_philo);
		int i = kill((*philos)[n_philo++].pid, SIGTERM);
		printf("child to kill == %d\n", (*philos)[n_philo].pid);
		printf("status kill == %d\n", i);
	}
	printf("kill all process\n");
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
		int i = sem_wait(phil->eating_num);
		// printf("death after wait id == %d ___ i == %d\n", phil->pos, i);
		if (shared->eating_number > 0 && phil->eating_count >= shared->eating_number)
		{
			sem_post(phil->eating_num);
			// printf("pid == %d\n", getpid());
			// printf("max == %d ____ num == %d\n", shared->max_eat, shared->num);
			// sem_post(phil->shared->finished);
			exit(0);
		}
		i = sem_post(phil->eating_num);
		// printf("death after post id == %d ___ i == %d\n", phil->pos, i);
		// sem_wait(phil->last_eat);
		if ((time - phil->last_meal) > phil->shared->time_to_die)
		{
			sem_wait(phil->eating_num);
			sem_wait(phil->shared->printer);
			printf("%d %d died\n", time, phil->pos);
			sem_post(phil->shared->finished);
			exit(1);
		}
		sem_post(phil->last_eat);
		upgraded_usleep(10);
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
	printf("threaad watchingf\n");
	kill_proce(philos, shared);
	printf("threaad finished\n");
	return (NULL);
}

