/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startProcess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:05:28 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/16 17:35:13 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

void	taking(t_philosopher *phil)
{
	sem_wait(phil->shared->forks);
	print_state("has taken a fork", phil);
}

void	give_and_sleep(t_philosopher *phil)
{
	sem_post(phil->shared->forks);
	sem_post(phil->shared->forks);
	print_state("is sleeping", phil);
	upgraded_usleep(phil->shared->time_to_sleep);
}

int	philos_start(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;

	shared->start_time = timevalue();
	n_philo = 0;
	while (n_philo < shared->num)
	{
		(*philos)[n_philo].pid = fork();
		if ((*philos)[n_philo].pid == 0)
			philo_life(&((*philos)[n_philo]));
		n_philo++;
	}
	if (pthread_create(&(shared->shinigami), NULL,
			wait_death, philos))
		return (0);
	return (1);
}

int	waiting_philos(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;
	int	code;

	n_philo = 0;
	code = 1;
	while (n_philo < shared->num)
	{
		if (waitpid((*philos)[n_philo].pid, NULL, 0) == -1)
			code = 0;
		n_philo++;
	}
	return (code);
}

int	philo_life(t_philosopher *phil)
{
	pthread_t	shinigami;

	pthread_create(&shinigami, NULL, end_philos, phil);
	if (phil->pos % 2 != 0)
		upgraded_usleep(phil->shared->time_to_eat);
	while (1)
	{
		if (phil->eating_count >= phil->shared->eating_number
			&& phil->shared->eating_number > 0)
			break ;
		taking(phil);
		taking(phil);
		print_state("is eating", phil);
		upgraded_usleep(phil->shared->time_to_eat);
		phil->eating_count++;
		sem_wait(phil->last_eat);
		phil->last_meal = timevalue() - phil->shared->start_time;
		sem_post(phil->last_eat);
		give_and_sleep(phil);
		print_state("is thinking", phil);
	}
	return (1);
}

