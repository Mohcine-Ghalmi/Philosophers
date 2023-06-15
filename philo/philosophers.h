/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:30:07 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/15 14:21:20 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# define MAX_VALUE 2147483647

typedef struct s_shared
{
	int				num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_eating;
	long			start_time;
	pthread_mutex_t	print_locker;
	int				is_dead;
	pthread_mutex_t	dead_locker;
	pthread_t		thread_checker;
}	t_shared;

typedef struct s_fork
{
	int				fork_used;
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				number;
	long			last_eat;
	pthread_mutex_t	last_eat_locker;
	int				eating_number;
	t_fork			*right_f;
	int				right_taken;
	t_fork			*left_f;
	int				left_taken;
	t_shared		*shared;
}	t_philosopher;

int		end_philo(t_philosopher *philosopher);
void	*shinigami(void *arg);
int		kill_philos(t_philosopher *philosopher);
void	fork_taker(char *fork_name, t_philosopher *philosopher);
void	detach_fork(char *fork_name, t_philosopher *philosopher);
void	detach_and_sleep(t_philosopher *philosopher);
void	*live_die(void *arg);
int		start_threads(t_philosopher **philosopheros, t_shared *shared);
int		thread_join(t_philosopher **philosopheros, t_shared *shared);
void	upgraded_usleep(long int time_in_ms);
void	my_printer(char *str, t_philosopher *philosopher);
long	timevalue(void);
long	ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	after_taking(t_philosopher *philosopher);

#endif
