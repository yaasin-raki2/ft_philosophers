#include <utils.h>

int ft_atoi(char *s) {
    int res = 0;
    int i = -1;
    while (s[++i] && s[i] >= '0' && s[i] <= '9')
        res = (res * 10) + (s[i] - '0');
    return res;
}