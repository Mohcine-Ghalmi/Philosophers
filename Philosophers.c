/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleeps <sleeps@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:33 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/25 13:33:00 by sleeps           ###   ########.fr       */
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
    }
    return (check_args(philosophers));
}

void    create_philosopher(t_philo *philosopher, long number_of_philosphers)
{
    int n_ph;

    n_ph = 0;
    if (!philosopher)
        return;
    while (n_ph < number_of_philosphers)
    {
        philosopher->number = n_ph + 1;
        philosopher->last_eat = 0;
        philosopher->thinking = 0;
        philosopher->last_eat = 0;
        pthread_mutex_init(philosopher->left_frok, NULL);
    }
}

int main(int argc, char **argv)
{
    t_shared *philosophers;
    t_philo *philosopher;
    long number_of_philosophers;

    if (argc == 5 || argc == 6)
    {
        number_of_philosophers = ft_atoi(argv[1]);
        if (number_of_philosophers <= 0)
        {
            printf("\033[31mError\n");
            return (0);
        }
        philosopher = malloc(sizeof(t_philo) * number_of_philosophers);
        philosophers = malloc(sizeof(t_shared));
        if (!philosopher || !philosopher)
            return 0;
        if (data_taking(philosophers, argv))
        {
            free(philosopher);
            free(philosophers);
            printf("\033[31minvalid arguments");
            return (0);
        }
        create_philosopher(philosopher, number_of_philosophers);
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
