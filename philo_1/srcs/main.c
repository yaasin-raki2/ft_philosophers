#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <options.h>
#include <utils.h>

void *thread_1_body(void *arg) {
    printf("Hey %s\n", (char *)arg);
    return NULL;
}

int main(int ac, char *av[ac]) {
    if (ac < 5)
        return 0;

    options_t options;
    options_t *op = &options;

    op->number_of_philosopher = ft_atoi(av[1]);
    op->time_to_die = ft_atoi(av[2]);
    op->time_to_eat = ft_atoi(av[3]);
    op->time_to_sleep = ft_atoi(av[4]);
    // options->number_of_times_each_philosopher_must_eat;

    printf("%d\n", op->number_of_philosopher);

    pthread_t thread_1;
    pthread_t thread_2;

    pthread_create(&thread_1, NULL, thread_1_body, "Yassine");
    pthread_create(&thread_2, NULL, thread_1_body, "Monokuma");

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    // pthread_detach(thread_1);
    // pthread_detach(thread_2);

    // pthread_exit(NULL);

    printf("1337\n");

    return 0;
}