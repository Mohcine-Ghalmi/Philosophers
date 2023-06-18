/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:05:21 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/19 00:26:03 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

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

void	init_sem(t_shared *shared)
{
	sem_unlink("forks");
	sem_unlink("printer");
	sem_unlink("done");
	sem_unlink("optional");
	shared->forks = sem_open("forks", O_CREAT, 0644, shared->num);
	shared->printer = sem_open("printer", O_CREAT, 0644, 1);
	shared->finished = sem_open("done", O_CREAT, 0644, 0);
	shared->opt = sem_open("optional", O_CREAT, 0644, 1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	signe;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (signe * res);
}

int	init_shared(t_shared *shared, int argc, char **argv)
{
	if (argc < 5)
		return (0);
	shared->num = ft_atoi(argv[1]);
	shared->time_to_die = ft_atoi(argv[2]);
	shared->time_to_eat = ft_atoi(argv[3]);
	shared->time_to_sleep = ft_atoi(argv[4]);
	shared->eating_number = -1;
	shared->max_eat = 0;
	if (argc > 5)
	{
		shared->eating_number = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) < 0)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_shared			shared;
	t_philosopher		*philos;
	pthread_t			thread2;

	thread2 = NULL;
	init_shared(&shared, argc, argv);
	if (check_args(&shared))
		return (0);
	init_sem(&shared);
	if (alloc_philos(&philos, &shared) == 0)
		return (0);
	if (philos_start(&philos, &shared) == 1)
		kill_proce(&philos, &shared);
	pthread_detach(shared.shinigami);
	sem_unlink("forks");
	sem_unlink("printer");
	sem_unlink("done");
	sem_unlink("optional");
	free(philos);
	sem_close(shared.forks);
	sem_close(shared.printer);
	sem_close(shared.finished);
	sem_close(shared.opt);
	return (0);
}
