/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:11 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/01 15:53:05 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
# define max_value 2147483647

typedef struct philosophers
{
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long number_of_times_each_philosopher_must_eat;
}           t_shared;

typedef struct philosopher
{
    long long last_eat;
    int waiting;
    int number;
    int eating_number;
    int philo_life_time;
    pthread_mutex_t right_fork;
    pthread_mutex_t *left_fork;
    pthread_t philo_thread;
    t_shared *shared;
}   t_philo;

long	ft_atoi(const char *str);
int check_args(t_shared *philosophers);
long long timevalue(void);
void    take_forks(t_philo *philosopher);
void    *lifephilo(void  *arg);
int data_taking(t_shared *philosophers, char **argv);
void	my_usleep(long milis);
int   check_death(t_philo *philosopher);

#endif