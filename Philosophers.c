/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:33 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/05 21:34:45 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	data_taking(t_shared *philosophers, char **argv)
{
	philosophers->time_to_die = ft_atoi(argv[2]);
	philosophers->time_to_eat = ft_atoi(argv[3]);
	philosophers->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		philosophers->number_of_times_each_philosopher_must_eat
			= ft_atoi(argv[5]);
		if (philosophers->number_of_times_each_philosopher_must_eat < 0)
			return (1);
	}
	else
		philosophers->number_of_times_each_philosopher_must_eat
			= -1;
	return (check_args(philosophers));
}

void	create_philosophers(t_philo **philosopher, long number_of_philosophers)
{
	int	n_ph;

	n_ph = 0;
	while (n_ph < number_of_philosophers)
	{
		philosopher[n_ph]->number = n_ph + 1;
		philosopher[n_ph]->last_eat = 0;
		if (n_ph == number_of_philosophers - 1)
			philosopher[n_ph]->left_fork = &(philosopher[0]->right_fork);
		else
			philosopher[n_ph]->left_fork = &(philosopher[n_ph + 1]->right_fork);
		n_ph++;
	}
}

void	destro(t_philo **philosopher, long long number_of_philosophers)
{
	int	i;

	i = -1;
	while (++i < number_of_philosophers)
	{
		pthread_mutex_destroy(&philosopher[i]->right_fork);
		pthread_mutex_destroy(philosopher[i]->death_print);
		pthread_mutex_destroy(philosopher[i]->l_eat);
		pthread_mutex_destroy(philosopher[i]->num_eating);
		pthread_mutex_destroy(philosopher[i]->left_fork);
	}
}

void	start_threads(t_philo **philosopher, long number_of_philosophers)
{
	int			i;
	long long	time;
	pthread_mutex_t	*end;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*n_eat;
	pthread_mutex_t	*death;

	time = timevalue();
	i = -1;
	end = malloc(sizeof(pthread_mutex_t));
	eat = malloc(sizeof(pthread_mutex_t));
	n_eat = malloc(sizeof(pthread_mutex_t));
	death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(eat,  NULL);
	pthread_mutex_init(end, NULL);
	pthread_mutex_init(n_eat, NULL);
	while (++i < number_of_philosophers)
	{
		philosopher[i]->shared->time_start = time;
		philosopher[i]->l_eat = eat;
		philosopher[i]->num_eating = n_eat;
		philosopher[i]->death_print = death;
	}
	i = -1;
	while (++i < number_of_philosophers)
	{
		philosopher[i]->last_eat = time;
		if (pthread_create(&(philosopher[i]->philo_thread), NULL, lifephilo, philosopher[i]))
			return ;
	}
	i = -1;
	while (++i < number_of_philosophers)
		pthread_detach(philosopher[i]->philo_thread);
	usleep(200);
	i = 0;
	while (1)
	{
		pthread_mutex_lock(end);
		pthread_mutex_lock(philosopher[i]->l_eat);
		if (timevalue() - philosopher[i]->last_eat >= philosopher[i]->shared->time_to_die)
		{
			pthread_mutex_lock(philosopher[i]->death_print);
			printf("%lld %d is die\n", timevalue() - philosopher[i]->last_eat, philosopher[i]->number);
			break ;
		}
		pthread_mutex_unlock(philosopher[i]->l_eat);
		pthread_mutex_lock(philosopher[i]->num_eating);
		if (philosopher[i]->eating_number == philosopher[i]->shared->number_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_unlock(philosopher[i]->num_eating);
			pthread_mutex_unlock(end);
			break;
		}
		pthread_mutex_unlock(end);
		pthread_mutex_unlock(philosopher[i]->num_eating);
		i++;
		if (i == number_of_philosophers)
			i = 0;
	}
	destro(philosopher, number_of_philosophers);
	free(end);
	free(death);
	free(n_eat);
	free(eat);
	return ;
}

void f()
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_philo **philosopher;
	long number_of_philosophers;
	int n;

	n = 0;
	atexit(f);
	if (argc == 5 || argc == 6)
	{
		number_of_philosophers = ft_atoi(argv[1]);
		if (number_of_philosophers <= 0)
		{
			printf("\033[31mError\n");
			return (0);
		}
		philosopher = malloc(sizeof(t_philo *) * number_of_philosophers);
		if (!philosopher)
			return 0;
		while (n < number_of_philosophers)
		{
			philosopher[n] = malloc(sizeof(t_philo));
			pthread_mutex_init(&philosopher[n]->right_fork, NULL);
			philosopher[n]->shared = malloc(sizeof(t_shared));
			if (data_taking(philosopher[n]->shared, argv))
			{
				n = 0;
				while (n < number_of_philosophers)
				{
					free(philosopher[n]->shared);
					free(philosopher[n]);
					n++;
				}
				free(philosopher);
				printf("\033[31minvalid arguments");
				return (0);
			}
			++n;
		}
		create_philosophers(philosopher, number_of_philosophers);
		start_threads(philosopher, number_of_philosophers);
		n = 0;
		while (n < number_of_philosophers)
		{
			free(philosopher[n]->shared);
			free(philosopher[n]);
			n++;
		}
		free(philosopher);
	}
	else
		printf("\033[31minvalid arguments");
	return (0);
}
