/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/01 15:55:12 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long timevalue(void)
{
    struct timeval timeval;

    gettimeofday(&timeval, NULL);
    return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

int   check_death(t_philo *philosopher)
{
    if (philosopher->philo_life_time >= philosopher->shared->time_to_die || philosopher->eating_number == philosopher->shared->number_of_times_each_philosopher_must_eat)
    {
        printf("%lld %d died\n", timevalue() - philosopher->last_eat , philosopher->number);
        return 0;
    }
    return 1;
}

void    start_eating(t_philo *philosopher)
{
    my_usleep(philosopher->shared->time_to_eat);
    philosopher->last_eat = timevalue();
    philosopher->philo_life_time += philosopher->shared->time_to_eat;
    printf("%lld %d is eating\n", timevalue() -  philosopher->last_eat, philosopher->number);
    philosopher->eating_number++;
    pthread_mutex_unlock(&(philosopher->right_fork));
    pthread_mutex_unlock((philosopher->left_fork));
}

void    take_forks(t_philo *philosopher)
{
    pthread_mutex_lock(&(philosopher->right_fork));
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->last_eat ,philosopher->number);
    pthread_mutex_lock(philosopher->left_fork);
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->last_eat ,philosopher->number);
    // start_eating(philosopher);
}

void    start_sleeping(t_philo *philosopher)
{
    my_usleep(philosopher->shared->time_to_sleep);
    philosopher->philo_life_time += philosopher->shared->time_to_sleep;
    printf("%lld %d is sleeping\n", timevalue() - philosopher->last_eat, philosopher->number);
}

void    *lifephilo(void  *arg)
{
    t_philo *philosopher;

    philosopher = (t_philo *)arg;
    if (philosopher->number % 2 == 0)
    {
        // first waiting time for the other philosophers
        philosopher->philo_life_time = philosopher->shared->time_to_eat;
        my_usleep(philosopher->shared->time_to_eat);
    }
    //check if philos meals nums or time are done
    while (check_death(philosopher))
    {
        take_forks(philosopher);
        start_eating(philosopher);
        start_sleeping(philosopher);
        printf("%lld %d is thinking\n", timevalue() - philosopher->last_eat, philosopher->number);
    }
    return (NULL);
}
