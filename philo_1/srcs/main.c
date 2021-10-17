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

void *routine(void *arg) {
    philo_t *philo = (philo_t *)arg;
    while (1) {
        printf("Philosopher %d is thinking\n", philo->id);

        pthread_mutex_lock(&(*philo->forks)[philo->id]);
        printf("Philosopher %d has taken the %dth fork\n", philo->id, philo->id);
        pthread_mutex_lock(&(*philo->forks)[(philo->id + 1) % (philo->ops->np)]);
        printf("Philosopher %d has taken the %dth fork\n", philo->id, (philo->id + 1) % (philo->ops->np));

        printf("Philosopher %d is eating for %d seconds\n", philo->id, philo->ops->te);
        sleep(philo->ops->te);

        pthread_mutex_unlock(&(*philo->forks)[philo->id]);
        pthread_mutex_unlock(&(*philo->forks)[(philo->id + 1) % (philo->ops->np)]);

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

    pthread_mutex_t *forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ops.np);
    int i = 0;
    while (i < ops.np) {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }

    philo_t philos[ops.np];
    i = 0;
    while (i < ops.np) {
        philos[i].id = i;
        philos[i].ops = &ops;
        philos[i].forks = &forks;
        pthread_create(&(philos[i].th), NULL, &routine, &(philos[i]));
        i++;
    }

    i = -1;
    while (++i < ops.np)
        pthread_join(philos[i].th, NULL);

    i = -1;
    while (++i < ops.np)
        pthread_mutex_destroy(&forks[i]);

    return EXIT_SUCCESS;
}