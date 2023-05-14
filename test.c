#include "philosophers.h"

int data_taking(t_shared *philosophers, char **argv)
{
    philosophers->time_to_die = ft_atoi(argv[2]);
    philosophers->time_to_eat = ft_atoi(argv[3]);
    philosophers->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        philosophers->number_of_times_each_philosopher_must_eat =  ft_atoi(argv[5]);
    return (check_args(philosophers));
}

int philo_table(t_philo *philo, long number_of_philosophers)
{
    int i;
    long start_time;

    i = 0;
    start_time = timevalue();
    while (i < number_of_philosophers)
    {
        philo[i].last_eat = 0;
    }
}

int main(int argc, char **argv)
{
    t_shared *philosophers;
    t_philo *philo;
    long number_of_philosophers;

    if (argc == 5 || argc == 6)
    {
        number_of_philosophers = ft_atoi(argv[1]);
        if (number_of_philosophers <= 0)
            return (0);
        philo = malloc(sizeof(t_philo) * number_of_philosophers);
        if (data_taking(philosophers, argv))
        {
            free(philosophers);
            printf("\033[31minvalid arguments");
            return (0);
        }
        else
        {
            // philo_table()
        }
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
