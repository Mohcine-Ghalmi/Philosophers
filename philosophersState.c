/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/05 21:01:32 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long timevalue(void)
{
    struct timeval timeval;

    gettimeofday(&timeval, NULL);
    return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void    start_eating(t_philo *philosopher)
{
    pthread_mutex_lock(philosopher->death_print);
    printf("%lld %d is eating\n", timevalue() -  philosopher->shared->time_start, philosopher->number);
    pthread_mutex_unlock(philosopher->death_print);
    my_usleep(philosopher->shared->time_to_eat);
    pthread_mutex_lock(philosopher->l_eat);
    philosopher->last_eat = timevalue();
    pthread_mutex_unlock(philosopher->l_eat);
    pthread_mutex_lock(philosopher->num_eating);
    philosopher->eating_number++;
    pthread_mutex_unlock(philosopher->num_eating);
    pthread_mutex_unlock(&(philosopher->right_fork));
    pthread_mutex_unlock((philosopher->left_fork));
}

void    take_forks(t_philo *philosopher)
{
    pthread_mutex_lock(&(philosopher->right_fork));
    pthread_mutex_lock(philosopher->death_print);
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
    pthread_mutex_unlock(philosopher->death_print);
    pthread_mutex_lock(philosopher->left_fork);
    pthread_mutex_lock(philosopher->death_print);
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
    pthread_mutex_unlock(philosopher->death_print);
}

void   start_sleeping(t_philo *philosopher)
{
    pthread_mutex_lock(philosopher->death_print);
    printf("%lld %d is sleeping\n", timevalue() - philosopher->shared->time_start, philosopher->number);
    pthread_mutex_unlock(philosopher->death_print);
    my_usleep(philosopher->shared->time_to_sleep);
}

void    *lifephilo(void  *arg)
{
    t_philo *philosopher;

    philosopher = (t_philo *)arg;
    if (philosopher->number % 2 == 0)
        usleep(200);
    while (1)
    {
        take_forks(philosopher);
        start_eating(philosopher);
        start_sleeping(philosopher);
        pthread_mutex_lock(philosopher->death_print);
        printf("%lld %d is thinking\n", timevalue() - philosopher->shared->time_start, philosopher->number);
        pthread_mutex_unlock(philosopher->death_print);
    }
    return (NULL);
}
