#include <options.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <utils.h>

// #define NUMBER_OF_PHILOSOPHERS 5

pthread_mutex_t mtx;

void ops_init(ops_t *ops, char **av) {
    ops->np = ft_atoi(av[1]);
    ops->td = ft_atoi(av[2]);
    ops->te = ft_atoi(av[3]);
    ops->ts = ft_atoi(av[4]);
}

void forks_init() {
}

void *routine(void *arg) {
    philo_t *philo = (philo_t *)arg;
    while (1) {
        printf("Philosopher %d is thinking\n", philo->id);

        pthread_mutex_lock(&mtx);

        printf("Philosopher %d is eating for %d seconds\n", philo->id, philo->ops->te);
        sleep(philo->ops->te);

        pthread_mutex_unlock(&mtx);

        printf("Philosopher %d is sleeping for %d seconds\n", philo->id, philo->ops->ts);
        sleep(philo->ops->ts);
    }
    return NULL;
}

int main(int ac, char *av[ac]) {
    if (ac < 5) {
        printf("\e[31m- Usage: %s <number of philosophers> <time to eat> <time to die> <time to sleep>\e[0m\n", av[0]);
        return EXIT_FAILURE;
    }

    ops_t ops;
    ops_init(&ops, av);

    philo_t philos[ops.np];

    pthread_mutex_init(&mtx, NULL);

    int i = 0;
    while (i < ops.np) {
        philos[i].id = i;
        philos[i].ops = &ops;
        pthread_create(&(philos[i].th), NULL, &routine, &(philos[i]));
        i++;
    }

    i = -1;
    while (++i < ops.np)
        pthread_join(philos[i].th, NULL);

    pthread_mutex_destroy(&mtx);

    return EXIT_SUCCESS;
}