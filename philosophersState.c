/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/04 16:55:20 by mghalmi          ###   ########.fr       */
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
    // pthread_mutex_unlock(philosopher->end->death);
    if (timevalue() - philosopher->last_eat > philosopher->shared->time_to_die)
    {
        pthread_mutex_lock(philosopher->end->death);
        philosopher->end->die = 1;
        pthread_mutex_unlock(philosopher->end->death);
        printf("%lld %d died\n", timevalue() - philosopher->shared->time_start , philosopher->number);
        // pthread_mutex_lock(philosopher->end->death);
        return 0;
    }
    else if (philosopher->eating_number  == philosopher->shared->number_of_times_each_philosopher_must_eat)
        return 0;
    return 1;
}

int    start_eating(t_philo *philosopher)
{
    printf("%lld %d is eating\n", timevalue() -  philosopher->shared->time_start, philosopher->number);
    if (my_usleep(philosopher->shared->time_to_eat, philosopher) == 0)
        return 0;
    philosopher->last_eat = timevalue();
    philosopher->shared->time_to_die += philosopher->shared->time_to_eat;
    philosopher->eating_number++;
    pthread_mutex_unlock(&(philosopher->right_fork));
    pthread_mutex_unlock((philosopher->left_fork));
    return 1;
}

void    take_forks(t_philo *philosopher)
{
    pthread_mutex_lock(&(philosopher->right_fork));
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
    pthread_mutex_lock(philosopher->left_fork);
    printf("%lld %d has taken a fork\n", timevalue() - philosopher->shared->time_start ,philosopher->number);
}

int    start_sleeping(t_philo *philosopher)
{
    printf("%lld %d is sleeping\n", timevalue() - philosopher->shared->time_start, philosopher->number);
    if (my_usleep(philosopher->shared->time_to_sleep,  philosopher) == 0)
        return 0;
    philosopher->shared->time_to_die += philosopher->shared->time_to_sleep;
    return 1;
}

int find_death(t_philo *philosopher)
{
    int i;
    t_end *end;

    i = 0;
    end = philosopher->end;
    while (i < philosopher->number)
    {
        if (end->die == 1)
            return 0;
        end = end->next;
        i++;
    }
    return 1;
}

void    *lifephilo(void  *arg)
{
    t_philo *philosopher;

    philosopher = (t_philo *)arg;
    if (philosopher->number % 2 == 0)
        usleep(100);
    while (1)
    {
        pthread_mutex_lock(philosopher->end->death);
        if (find_death(philosopher) == 0)
        {
            pthread_mutex_unlock(philosopher->end->death);
            break;
        }
        pthread_mutex_unlock(philosopher->end->death);
        take_forks(philosopher);
        pthread_mutex_lock(philosopher->end->death);
        if (start_eating(philosopher) == 0 || start_sleeping(philosopher) == 0)
        {
            philosopher->end->die = 1;
            pthread_mutex_unlock(philosopher->end->death);
            return (NULL);
        }
        pthread_mutex_unlock(philosopher->end->death);
        printf("%lld %d is thinking\n", timevalue() - philosopher->shared->time_start, philosopher->number);
    }
    return (NULL);
}
