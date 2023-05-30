/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sleeps <sleeps@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/30 23:27:52 by sleeps           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long timevalue(void)
{
    struct timeval timeval;

    gettimeofday(&timeval, NULL);
    return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void    take_forks(t_philo *philosopher)
{
    if (pthread_mutex_lock(&(philosopher->right_fork)) == 0)
        printf("%d has taken a right fork\n", philosopher->number);
    // pthread_mutex_unlock(&(philosopher->right_fork));
    if (pthread_mutex_lock(philosopher->left_fork) == 0)
        // printf("%d has taken a left fork\n", philosopher->number);
    pthread_mutex_unlock((philosopher->left_fork));
}

void    start_eating(t_philo *philosopher, t_shared *philosophers)
{
    printf("%d is eating\n", philosopher->number);
    philosopher->last_eat = timevalue();
    usleep(philosophers->time_to_eat / 1000);
}

void    *lifephilo(void  *arg)
{
    t_philo *philosopher = (t_philo *)arg;
    if (philosopher->number % 2)
        usleep(100);
    take_forks(philosopher);
    // start_eating(philosopher);
    return (NULL);
}