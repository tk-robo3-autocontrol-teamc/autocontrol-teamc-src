#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *threadOdm(void *arg)
{
    for (int i = 0; i < 3; i++) {
        printf("I'm threadOdm: %d\n", i);
        sleep(1);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread;

    if (pthread_create(&thread, NULL, threadOdm, NULL) != 0) {
        printf("Error: Failed to create thread.\n");
        exit(1);
    }

    for (int i = 0; i < 5; i++) {
        printf("I7 main: %d\n", i);
        sleep(1);
    }

    return 0;
}