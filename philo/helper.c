/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mghalmi <mghalmi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:29:59 by mghalmi           #+#    #+#             */
/*   Updated: 2023/06/18 15:08:33 by mghalmi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	upgraded_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = timevalue();
	while ((timevalue() - start_time) < time_in_ms)
		usleep(100);
}

void	my_printer(char *str, t_philosopher *philosopher)
{
	long	now_time;

	now_time = timevalue() - philosopher->shared->start_time;
	pthread_mutex_lock(&(philosopher->shared->print_locker));
	if (!end_philo(philosopher))
		printf("%ld %d %s\n", now_time, philosopher->number, str);
	pthread_mutex_unlock(&(philosopher->shared->print_locker));
}

long	timevalue(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long	ft_atoi(const char *str)
{
	long	res;
	int		i;
	int		signe;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe *= -1;
	if (!str[i])
		signe = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	if (str[i] || signe == 0)
		return (-1);
	return (signe * res);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	if (n == 0)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] && str2[i] && str1[i] == str2[i] && --n)
		++i;
	return (str1[i] - str2[i]);
}
