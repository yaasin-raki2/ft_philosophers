#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct timeval t0;
    struct timeval t1;
    // gettimeofday(&tv, &tz);
    // long int old = tv.tv_usec;
    // printf("%lu\n", old);
    // sleep(2);
    // gettimeofday(&tv, &tz);
    // long int now = tv.tv_usec;
    // printf("%lu\n", now);
    // long int elapsed = now - old;
    // printf("%lu\n", elapsed);
    gettimeofday(&t0, NULL);
    sleep(1);
    gettimeofday(&t1, NULL);
    // long elapsed = t1.tv_usec - t0.tv_usec;
    // printf("%lu\n", elapsed);
    long elapsed = ((t1.tv_sec - t0.tv_sec) * 1000000 + t1.tv_usec) - t0.tv_usec;
    printf("%ld microseconds\n", elapsed);
    printf("%ld miliseconds\n", elapsed / 1000);
    return 0;
}