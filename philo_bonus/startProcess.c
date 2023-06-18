/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startProcess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:05:28 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/19 00:08:21 by mghalmi          ###   ########.fr       */
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
		{
			printf("before %d\n", getpid());
			philo_life(&((*philos)[n_philo]));
			printf("after %d\n", getpid());
			exit(0);
		}
		n_philo++;
	}
	// if (pthread_create(&(shared->shinigami), NULL,wait_death, philos))
	// 	return (0);
	return (1);
}

int	waiting_philos(t_philosopher **philos, t_shared *shared)
{
	int	n_philo;
	int	code;
	int status;
	int eat_max = 0;
	n_philo = 0;
	code = 1;
	(void)philos;
	(void)shared;
	while (1)
	{
		waitpid(0, &status, 0);
		// printf("status == %d\n", WEXITSTATUS(status));
		// printf("max == %d ____ num == %d\n", shared->max_eat, shared->num);
		if (WEXITSTATUS(status) != 0)
			return (code);
		else
			eat_max++;
		if (eat_max == shared->num)
		{
			return (0);
		}
	}
	return (code);
}

int	philo_life(t_philosopher *phil)
{
	pthread_t	shinigami;
	
	pthread_create(&shinigami, NULL, end_philos, phil);
	pthread_detach(shinigami);
	while (1)
	{
		// sem_wait(phil->eating_num);
		// if (phil->eating_count >= phil->shared->eating_number && phil->shared->eating_number > 0)
		// {
		// 	// sem_post(phil->eating_num);
		// 	break ;
		// }
		// sem_post(phil->eating_num);
		taking(phil);
		taking(phil);
		print_state("is eating", phil);
		upgraded_usleep(phil->shared->time_to_eat);
		int i = sem_wait(phil->eating_num);
		// printf("after wait id == %d ___ i == %d\n", phil->pos, i);
		phil->eating_count++;
		i = sem_post(phil->eating_num);
		// printf("after post id == %d ___ i == %d\n", phil->pos, i);
		sem_wait(phil->last_eat);
		phil->last_meal = timevalue() - phil->shared->start_time;
		sem_post(phil->last_eat);
		give_and_sleep(phil);
		print_state("is thinking", phil);
	}
	// sem_post(phil->shared->finished);
	return (1);
}
