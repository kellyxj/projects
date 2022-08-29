#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void print_args(int argc, char* argv[], char* envp[]);
int snooze(int secs);

void sigint_handler(int sig) {
    
}

int main(int argc, char* argv[], char* envp[]) {
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        printf("signal error");

    snooze(atoi(argv[1]));
    
}

void print_args(int argc, char* argv[], char* envp[]) {
    int index = 0;
    char* current = envp[index];

    while(current != NULL) {
        printf("%s\n", envp[index]);
        index += 1;
        current = envp[index];
    }
    index = 0;
    current = argv[index];

    while(current != NULL) {
        printf("%s\n", argv[index]);
        index += 1;
        current = argv[index];
    }
}

int snooze(int secs) {
    int remain = sleep(secs);
    printf("slept for %d out of %d secs", secs-remain, secs);
}