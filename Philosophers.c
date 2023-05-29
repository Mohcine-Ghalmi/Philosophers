/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:33 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/29 19:52:30 by mghalmi          ###   ########.fr       */
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

void    free_prev_philos(t_philo **philosopher, long n_ph)
{
    while(n_ph--)
        free(philosopher[n_ph]);   
}

void    create_philosopher(t_philo **philosopher, long number_of_philosophers)
{
    int n_ph;

    n_ph = 0;
    while (n_ph < number_of_philosophers)
    {
        philosopher[n_ph] = malloc(sizeof(t_philo));
        if (!philosopher[n_ph])
        {
            free_prev_philos(philosopher, n_ph);
            return;
        }
        philosopher[n_ph]->number = n_ph + 1;
        philosopher[n_ph]->last_eat = 0;
        philosopher[n_ph]->thinking = 0;
        philosopher[n_ph]->last_eat = 0;
        pthread_mutex_init(&(philosopher[n_ph]->right_fork), NULL);
        if (n_ph == number_of_philosophers - 1)
            philosopher[n_ph]->left_fork = &(philosopher[0]->right_fork);
        else
            philosopher[n_ph]->left_fork = &(philosopher[n_ph + 1]->right_fork);
        n_ph++;
    }
}

void    start_threads(t_philo **philosopher, long number_of_philosophers, t_shared *philosophers)
{
    long long start_time;

    start_time = timevalue();
    int i = -1;
    while (++i < number_of_philosophers)
        pthread_create(&(philosopher[i]->philo_thread), NULL, take_forks, philosopher[i]);
    i = -1;
    while (++i < number_of_philosophers)
            pthread_join(philosopher[i]->philo_thread, NULL);
    (void)philosopher;
    (void)philosophers;
    (void)number_of_philosophers;
}

int main(int argc, char **argv)
{
    t_shared *philosophers;
    t_philo **philosopher;
    long number_of_philosophers;

    if (argc == 5 || argc == 6)
    {
        number_of_philosophers = ft_atoi(argv[1]);
        if (number_of_philosophers <= 0)
        {
            printf("\033[31mError\n");
            return (0);
        }
        philosopher = malloc(sizeof(t_philo *) * number_of_philosophers);
        philosophers = malloc(sizeof(t_shared));
        if (!philosopher || !philosophers)
            return 0;
        if (data_taking(philosophers, argv))
        {
            free(philosopher);
            free(philosophers);
            printf("\033[31minvalid arguments");
            return (0);
        }
        create_philosopher(philosopher, number_of_philosophers);
        start_threads(philosopher, number_of_philosophers, philosophers);
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
