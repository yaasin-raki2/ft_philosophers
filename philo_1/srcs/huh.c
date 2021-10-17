// #include <pthread.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

// pthread_mutex_t mtx;

// void *routine(void *available_fork) {
//     while (*(int *)available_fork > 0) {
//         pthread_mutex_lock(&mtx);
//         if (*(int *)available_fork > 0) {
//             *(int *)available_fork = *(int *)available_fork - 1;
//             printf("Philo %lu is Eating ...\n", pthread_self());
//             usleep(1000000);
//             *(int *)available_fork = *(int *)available_fork + 1;
//             break;
//         }
//         pthread_mutex_unlock(&mtx);
//     }
//     return NULL;
// }

// int main() {
//     pthread_t thread_1;
//     pthread_t thread_2;
//     pthread_t thread_3;

//     int available_fork = 2;

//     pthread_mutex_init(&mtx, NULL);

//     // int i = 0;

//     pthread_create(&thread_1, NULL, &routine, &available_fork);
//     pthread_create(&thread_2, NULL, &routine, &available_fork);
//     pthread_create(&thread_3, NULL, &routine, &available_fork);

//     pthread_join(thread_1, NULL);
//     pthread_join(thread_2, NULL);
//     pthread_join(thread_3, NULL);

//     pthread_mutex_destroy(&mtx);

//     return (0);
// }