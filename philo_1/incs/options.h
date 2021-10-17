#ifndef OPTIONS_H
#define OPTIONS_H

#include <pthread.h>

enum status {
    EATING,
    SLEEPING,
    THINKING
};

typedef struct ops_s {
    int np;
    int td;
    int te;
    int ts;
} ops_t;

typedef struct philo_s {
    // int ne;
    ops_t *ops;
    pthread_t th;
    int id;
    pthread_mutex_t **forks;
} philo_t;

#endif