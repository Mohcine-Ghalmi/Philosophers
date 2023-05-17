#include "philosophers.h"

int data_taking(t_shared *philosophers, char **argv)
{
    philosophers->time_to_die = ft_atoi(argv[2]);
    philosophers->time_to_eat = ft_atoi(argv[3]);
    philosophers->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
    {
        philosophers->number_of_times_each_philosopher_must_eat =  ft_atoi(argv[5]);
        if (philosophers->number_of_times_each_philosopher_must_eat < 0)
            return 1;
    }
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
        philo[i].number = i;
        philo[i].waiting = 0;
        philo[i].right_frok = NULL;
        philo[i].left_frok = NULL;
        pthread_mutex_init(&(philo[i].right_frok), NULL);
    
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
        {
            printf("\033[31mError\n");
            return (0);
        }
        philo = malloc(sizeof(t_philo) * number_of_philosophers);
        philosophers = malloc(sizeof(t_shared));
        if (data_taking(philosophers, argv))
        {
            free(philo);
            printf("\033[31minvalid arguments");
            return (0);
        }
        else
            philo_table(philo, number_of_philosophers);
    }
    else
        printf("\033[31minvalid arguments");
    return (0);
}
