/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophersState.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:04:04 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/29 18:31:29 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long timevalue(void)
{
    struct timeval timeval;

    gettimeofday(&timeval, NULL);
    return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void    *take_forks(void    *arg)
{
    t_philo *philosopher = (t_philo *)arg;
    if (pthread_mutex_lock(&(philosopher->right_fork)) == 0)
        printf("%d has taken a right fork\n", philosopher->number);
    if (pthread_mutex_lock(philosopher->left_fork) == 0)
        printf("%d has taken a left fork\n", philosopher->number);
    pthread_mutex_unlock(&(philosopher->right_fork));
    pthread_mutex_unlock((philosopher->left_fork));
    return (NULL);
}

// void    start_eating(t_philo *philosopher)
// {
    
// }