#include "philosophers.h"

int data_taking(t_philo *philosophers, char **argv)
{
    philosophers->number_of_philosophers = ft_atoi(argv[1]);
    philosophers->time_to_die = ft_atoi(argv[2]);
    philosophers->time_to_eat = ft_atoi(argv[3]);
    philosophers->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philosophers->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    return (check_args(philosophers));
}

int philo_table(t_philo *philosophers)
{
    
}

int main(int argc, char **argv)
{
    t_philo *philosophers;

    if (argc == 5 || argc == 6)
    {
        philosophers = malloc(sizeof(t_philo));
        if (data_taking(philosophers, argv))
        {
            free(philosophers);
            printf("\033[31minvalid arguments");
            return (0);
        }
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
h