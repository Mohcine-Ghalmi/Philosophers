/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/02 23:21:51 by mghalmi          ###   ########.fr       */
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
    if (philosopher->philo_life_time >= philosopher->shared->time_to_die)
    {
        printf("%lld %d died\n", timevalue() - philosopher->shared->time_start , philosopher->number);
        return 0;
    }else if (philosopher->eating_number  == philosopher->shared->number_of_times_each_philosopher_must_eat)
        return 0;
    return 1;
}

int    start_eating(t_philo *philosopher)
{
    philosopher->last_eat = timevalue();
    printf("%lld %d is eating\n", timevalue() -  philosopher->shared->time_start, philosopher->number);
    my_usleep(philosopher->shared->time_to_eat);
    philosopher->philo_life_time += philosopher->shared->time_to_eat;
    philosopher->eating_number++;
    pthread_mutex_unlock(&(philosopher->right_fork));
    pthread_mutex_unlock((philosopher->left_fork));
    if (!check_death(philosopher))
        return 0;
    return 1;
}

void    take_forks(t_philo *philosopher)
{
    pthread_mutex_lock(&(philosopher->right_fork));
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
    if (pthread_mutex_lock(philosopher->left_fork) != 0)
    {
        pthread_mutex_unlock(&(philosopher->right_fork));
        return ;
    }
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
}

int    start_sleeping(t_philo *philosopher)
{
    printf("%lld %d is sleeping\n", timevalue() - philosopher->shared->time_start, philosopher->number);
    my_usleep(philosopher->shared->time_to_sleep);
    philosopher->philo_life_time += philosopher->shared->time_to_sleep;
    if (!check_death(philosopher))
        return 0;
    return 1;
}

void    *lifephilo(void  *arg)
{
    t_philo *philosopher;

    philosopher = (t_philo *)arg;
    if (philosopher->number % 2 == 0)
    {
        philosopher->philo_life_time += philosopher->shared->time_to_eat;
        my_usleep(philosopher->shared->time_to_eat);
    }
    while (1)
    {
        take_forks(philosopher);
        start_eating(philosopher);
        start_sleeping(philosopher);
        printf("%lld %d is thinking\n", timevalue() - philosopher->shared->time_start, philosopher->number);
        if (!check_death(philosopher))
            break;
        philosopher->shared->time_to_die += timevalue() - philosopher->last_eat + philosopher->shared->time_to_die;
    }
    return (NULL);
}
