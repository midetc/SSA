#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        for (int i = 0; i < 5; i++) {
            printf("Child: %d\n", i);
            sleep(1);
        }
    } else {
        for (int i = 0; i < 5; i++) {
            printf("Parent: %d\n", i);
            sleep(1);
        }
    }
    return 0;
}
