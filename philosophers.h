/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 15:07:11 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/06 17:41:28 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# define MAX_VALUE 2147483647

typedef struct philosophers
{
	long long	time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		number_of_times_each_philosopher_must_eat;
	long long	time_start;
}		t_shared;

typedef struct philosopher
{
	long long		last_eat;
	int				number;
	int				eating_number;
	pthread_mutex_t	*l_eat;
	pthread_mutex_t	*num_eating;
	pthread_mutex_t	*death_print;
	pthread_mutex_t	right_fork;
	pthread_mutex_t	*left_fork;
	pthread_t		philo_thread;
	t_shared		*shared;
}		t_philo;

long			ft_atoi(const char *str);
int				check_args(t_shared *philosophers);
long long		timevalue(void);
void			take_forks(t_philo *philosopher);
void			*lifephilo(void *arg);
int				data_taking(t_shared *philosophers, char **argv);
void			my_usleep(long milis);
void			create_philosophers(t_philo **philosopher,
					long number_of_philosophers);
void			give_mutex(t_philo *philosopher, pthread_mutex_t *eat,
					pthread_mutex_t *n_eat, pthread_mutex_t *death);
void			fr(pthread_mutex_t *eat, pthread_mutex_t *n_eat,
					pthread_mutex_t *death);
int				philo_data_testing_alloc(t_philo **philosopher,
					long number_of_philosophers, char **argv);
void			fr2(t_philo **philosopher, long number_of_philosophers);

#endif