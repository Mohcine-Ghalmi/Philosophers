/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:33 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/01 15:52:01 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int data_taking(t_shared *philosophers, char **argv)
{
    philosophers->time_to_die = ft_atoi(argv[2]);
    philosophers->time_to_eat = ft_atoi(argv[3]);
    philosophers->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
    {
        philosophers->number_of_times_each_philosopher_must_eat =  ft_atoi(argv[5]);
        if (philosophers->number_of_times_each_philosopher_must_eat < 0)
            return 1;
    }else
        philosophers->number_of_times_each_philosopher_must_eat =  -1;
    return (check_args(philosophers));
}

void    create_philosophers(t_philo **philosopher, long number_of_philosophers)
{
    int n_ph;

	n_ph = 0;
    while (n_ph < number_of_philosophers)
    {
        philosopher[n_ph]->number = n_ph + 1;
        philosopher[n_ph]->last_eat = 0;
        philosopher[n_ph]->waiting = 0;
        philosopher[n_ph]->last_eat = 0;
        if (n_ph == number_of_philosophers - 1)
			philosopher[n_ph]->left_fork = &(philosopher[0]->right_fork);
        else
			philosopher[n_ph]->left_fork = &(philosopher[n_ph + 1]->right_fork);
        n_ph++;
    }
}

void    start_threads(t_philo **philosopher, long number_of_philosophers)
{
    int i = -1;
    while (++i < number_of_philosophers)
        philosopher[i]->last_eat = timevalue();
    i = -1;
    while (++i < number_of_philosophers)
        pthread_create(&(philosopher[i]->philo_thread), NULL, lifephilo, philosopher[i]);
    i = -1;
    while (++i < number_of_philosophers)
        pthread_join(philosopher[i]->philo_thread, NULL);
}

int main(int argc, char **argv)
{
    t_philo **philosopher;
    long number_of_philosophers;
	int n;

	n = 0;
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
			philosopher[n]->shared = malloc(sizeof(t_shared));
			if (data_taking(philosopher[n]->shared, argv))
        	{
        	    free(philosopher);
        	    printf("\033[31minvalid arguments");
        	    return (0);
        	}
            ++n;
		}
        create_philosophers(philosopher, number_of_philosophers);
        start_threads(philosopher, number_of_philosophers);
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
