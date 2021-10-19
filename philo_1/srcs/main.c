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
    gettimeofday(&ops->t0, NULL);
    gettimeofday(&ops->t1, NULL);
}

void *routine(void *arg) {
    philo_t *philo = (philo_t *)arg;
    long elapsed;
    long lm_elapsed;
    while (1) {
        gettimeofday(&philo->ops->t1, NULL);
        elapsed = (((philo->ops->t1.tv_sec - philo->ops->t0.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->ops->t0.tv_usec) / 1000;
        lm_elapsed = (((philo->ops->t1.tv_sec - philo->last_meal.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->last_meal.tv_usec) / 1000;
        printf("%lums | Philosopher %d is thinking | last_meal was %lums ago\n", elapsed, philo->id, lm_elapsed);

        pthread_mutex_lock(&(*philo->forks)[philo->id]);
        gettimeofday(&philo->ops->t1, NULL);
        elapsed = (((philo->ops->t1.tv_sec - philo->ops->t0.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->ops->t0.tv_usec) / 1000;
        lm_elapsed = (((philo->ops->t1.tv_sec - philo->last_meal.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->last_meal.tv_usec) / 1000;
        printf("%lums | Philosopher %d has taken the %dth fork | last_meal was %lums\n", elapsed, philo->id, philo->id, lm_elapsed);
        pthread_mutex_lock(&(*philo->forks)[(philo->id + 1) % (philo->ops->np)]);
        gettimeofday(&philo->ops->t1, NULL);
        gettimeofday(&philo->last_meal, NULL);
        elapsed = (((philo->ops->t1.tv_sec - philo->ops->t0.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->ops->t0.tv_usec) / 1000;
        lm_elapsed = (((philo->ops->t1.tv_sec - philo->last_meal.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->last_meal.tv_usec) / 1000;
        printf("%lums | Philosopher %d has taken the %dth fork | last_meal was %lums\n", elapsed, philo->id, (philo->id + 1) % (philo->ops->np), lm_elapsed);

        printf("%lums | Philospher %d is eating for %dms | last_meal wa %lums\n", elapsed, philo->id, philo->ops->te, lm_elapsed);
        usleep(philo->ops->te * 1000);

        pthread_mutex_unlock(&(*philo->forks)[philo->id]);
        pthread_mutex_unlock(&(*philo->forks)[(philo->id + 1) % (philo->ops->np)]);

        gettimeofday(&philo->ops->t1, NULL);
        elapsed = (((philo->ops->t1.tv_sec - philo->ops->t0.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->ops->t0.tv_usec) / 1000;
        lm_elapsed = (((philo->ops->t1.tv_sec - philo->last_meal.tv_sec) * 1000000 + philo->ops->t1.tv_usec) - philo->last_meal.tv_usec) / 1000;
        printf("%lums | Philosopher %d is sleeping for %dms | last_meal was %lums\n", elapsed, philo->id, philo->ops->ts, lm_elapsed);
        usleep(philo->ops->ts * 1000);
    }
    return NULL;
}

void staff(philo_t philos[], int size) {
    struct timeval curr;
    int lm_elapsed;
    while (1) {
        int i = 0;
        while (i < size) {
            gettimeofday(&curr, NULL);
            lm_elapsed = (((curr.tv_sec - philos[i].last_meal.tv_sec) * 1000000 + curr.tv_usec) - philos[i].last_meal.tv_usec) / 1000;
            if (lm_elapsed > philos[i].ops->td) {
                usleep(100);
                printf("died\n");
                return;
            }
            i++;
        }
    }
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
        gettimeofday(&philos[i].last_meal, NULL);
        pthread_create(&(philos[i].th), NULL, &routine, &(philos[i]));
        i++;
    }

    staff(philos, ops.np);

    return EXIT_SUCCESS;
}