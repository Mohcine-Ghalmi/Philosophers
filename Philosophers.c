/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleeps <sleeps@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:33 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/11 16:27:47 by sleeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

int	end_philo(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->l_eat);
	if (timevalue() - philosopher->last_eat
		> philosopher->shared->time_to_die)
	{
		pthread_mutex_lock(philosopher->death_print);
		printf("%lld %d died\n", timevalue()
			- philosopher->last_eat, philosopher->number);
		return (0);
	}
	pthread_mutex_unlock(philosopher->l_eat);
	pthread_mutex_lock(philosopher->num_eating);
	if (philosopher->eating_number
		== philosopher
		->shared->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_unlock(philosopher->num_eating);
		return (0);
	}
	pthread_mutex_unlock(philosopher->num_eating);
	return (1);
}

void	threads_start_end(t_philo **philosopher, long number_of_philosophers)
{
	int	i;

	i = -1;
	while (++i < number_of_philosophers)
	{
		philosopher[i]->last_eat = timevalue();
		if (pthread_create(&(philosopher[i]->philo_thread),
				NULL, lifephilo, philosopher[i]))
			return ;
	}
	i = -1;
	while (++i < number_of_philosophers)
		pthread_detach(philosopher[i]->philo_thread);
}

void	start_threads(t_philo **philosopher, long number_of_philosophers)
{
	int				i;
	pthread_mutex_t	*eat;
	pthread_mutex_t	*n_eat;
	pthread_mutex_t	*death;

	i = 0;
	eat = malloc(sizeof(pthread_mutex_t));
	n_eat = malloc(sizeof(pthread_mutex_t));
	death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(eat, NULL);
	pthread_mutex_init(n_eat, NULL);
	while (i < number_of_philosophers)
		give_mutex(philosopher[i++], eat, n_eat, death);
	threads_start_end(philosopher, number_of_philosophers);
	usleep(200);
	while (1)
	{
		if (i == number_of_philosophers)
			i = 0;
		if (end_philo(philosopher[i++]) == 0)
			break ;
	}
	destro(philosopher, number_of_philosophers);
	fr(eat, n_eat, death);
}

int	main(int argc, char **argv)
{
	t_philo	**philosopher;
	long	number_of_philosophers;

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
			return (0);
		if (philo_data_testing_alloc(philosopher,
				number_of_philosophers, argv) == 0)
			return (0);
		create_philosophers(philosopher, number_of_philosophers);
		start_threads(philosopher, number_of_philosophers);
		fr2(philosopher, number_of_philosophers);
	}
	else
		printf("\033[31minvalid arguments");
	return (0);
}
