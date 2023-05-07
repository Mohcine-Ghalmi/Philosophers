#include "philosophers.h"

void *threadFunc(void *arg)
{
    char *s;
    static int countThreads = 1;

    s = (char *)arg;
    printf("%s %d\n", s, countThreads++);
    return (void *) strlen(s);
}

int main(void)
{
    pthread_t Thread1;
    pthread_t Thread2;
    pthread_t Thread3;
    void *res;

    pthread_create(&Thread1, NULL, threadFunc, "i'm The Thread number");
    pthread_create(&Thread2, NULL, threadFunc, "i'm The Thread number");
    pthread_create(&Thread3, NULL, threadFunc, "i'm The Thread number");
    pthread_join(Thread1, &res);
    pthread_join(Thread2, &res);
    pthread_join(Thread3, &res);
    // pthread_detach(pthread_self());
    // usleep(40000);
    printf("Threads returned %ld", (long)res);
    return 0;
}
