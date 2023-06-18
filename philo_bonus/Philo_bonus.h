/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:43:31 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/18 23:52:54 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
# include <signal.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>
# define MAX_VALUE 2147483647

typedef struct s_shared
{
	pthread_t	shinigami;
	int			num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			eating_number;
	int			max_eat;
	long		start_time;
	sem_t		*printer;
	sem_t		*forks;
	sem_t		*finished;
	sem_t		*opt;
}	t_shared;

typedef struct s_phil
{
	pid_t		pid;
	int			pos;
	long		last_meal;
	sem_t		*last_eat;
	sem_t		*eating_num;
	int			eating_count;
	t_shared	*shared;
}	t_philosopher;

void	*end_philos(void *arg);
void	*wait_death(void *arg);
int		kill_proce(t_philosopher **philos, t_shared *shared);
void	taking(t_philosopher *phil);
void	give_and_sleep(t_philosopher *phil);
int		alloc_philos(t_philosopher **philos, t_shared	*shared);
int		init_shared(t_shared *shared, int argc, char **argv);
int		philo_life(t_philosopher *phil);
int		philos_start(t_philosopher **philos, t_shared *shared);
int		waiting_philos(t_philosopher **philos, t_shared *shared);
void	upgraded_usleep(long int time_in_ms);
void	print_state(char *str, t_philosopher *phil);
long	timevalue(void);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
