#include "philosophers.h"

long	ft_atoi(const char *str)
{
	long	res;
	long	i;
	int	signe;

	res = 0;
	i = 0;
	signe = 1;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (signe * res);
}

int check_args(t_philo *philosophers)
{
    if (philosophers->number_of_philosophers > 0)
        if (philosophers->time_to_die >= 60 && philosophers->time_to_die <= max_value) // max int
            if (philosophers->time_to_eat >= 60 && philosophers->time_to_eat <= max_value) // max int
                if (philosophers->time_to_sleep >= 60 && philosophers->time_to_sleep <= max_value) // max int
                    return 0;
    return 1;
}

int main(int argc, char **argv)
{
    t_philo *philosophers;

    if (argc == 5 || argc == 6)
    {
        philosophers = malloc(sizeof(t_philo));
        philosophers->number_of_philosophers = ft_atoi(argv[1]);
        philosophers->time_to_die = ft_atoi(argv[2]);
        philosophers->time_to_eat = ft_atoi(argv[3]);
        philosophers->time_to_sleep = ft_atoi(argv[4]);
        if (check_args(philosophers) == 1)
        {
            free(philosophers);
            printf("\033[31minvalid arguments");
            return (0);
        }
        if (argc == 5)
            printf("philosophres number %ld || die %ld || eat %ld || sleep %ld\n",
                philosophers->number_of_philosophers, philosophers->time_to_die, philosophers->time_to_eat, philosophers->time_to_sleep);
        else
        {
            philosophers->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
            printf("philosophres number %ld || die %ld || eat %ld || sleep %ld || rotine %ld\n",
                philosophers->number_of_philosophers, philosophers->time_to_die, philosophers->time_to_eat, philosophers->time_to_sleep, philosophers->number_of_times_each_philosopher_must_eat);
        }
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
