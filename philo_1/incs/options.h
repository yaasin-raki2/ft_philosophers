#ifndef OPTIONS_H
#define OPTIONS_H

typedef struct options_s {
    int number_of_philosopher;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int *number_of_times_each_philosopher_must_eat;
} options_t;

#endif