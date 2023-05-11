/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:11 by mghalmi           #+#    #+#             */
/*   Updated: 2023/05/11 18:19:53 by mghalmi          ###   ########.fr       */
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
    long number_of_philosophers;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long number_of_times_each_philosopher_must_eat;
}           t_philo;

long	ft_atoi(const char *str);
int check_args(t_philo *philosophers);
long long timevalue(void);

#endif