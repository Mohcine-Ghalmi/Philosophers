/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creatPhilosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 13:05:15 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/18 22:06:13 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philo_bonus.h"

int	len_int(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		i;
	char	*res;

	i = 0;
	len = len_int(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		i = 1;
	}
	while (len-- > i)
	{
		if (n < 0)
			res[len] = '0' + n % 10 * (-1);
		else
			res[len] = '0' + n % 10;
		n = n / 10;
	}
	return (res);
}

void	init_philosophero(t_philosopher *phil, t_shared *shared, int n_philo)
{
	char	*sem_name;
	char	*sem_eating;

	phil->shared = shared;
	phil->pos = n_philo + 1;
	phil->last_meal = 0;
	phil->eating_count = 0;
	sem_name = ft_strjoin("sem", ft_itoa(phil->pos));
	sem_eating = ft_strjoin("eat", ft_itoa(phil->pos));
	sem_unlink(sem_name);
	sem_unlink(sem_eating);
	phil->last_eat = sem_open(sem_name, O_CREAT, 0644, 1);
	phil->eating_num = sem_open(sem_eating, O_CREAT, 0644, 1);
	// sem_unlink(sem_eating);
	// sem_unlink(sem_name);
	free(sem_name);
	free(sem_eating);
}

int	alloc_philos(t_philosopher **philos, t_shared	*shared)
{
	int	n_philo;

	*philos = malloc(sizeof(t_philosopher) * shared->num);
	if (!(*philos))
		return (0);
	n_philo = 0;
	while (n_philo < shared->num)
	{
		init_philosophero(&(*philos)[n_philo], shared, n_philo);
		n_philo++;
	}

	return (1);
}

