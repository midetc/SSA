#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int try_open(const char *path, int flags) {
    int fd = open(path, flags);
    if (fd < 0) {
        printf("%s %s: %s\n",
               (flags & O_RDONLY) ? "read" : "write",
               path, strerror(errno));
    } else {
        printf("%s %s: OK\n",
               (flags & O_RDONLY) ? "read" : "write",
               path);
        close(fd);
    }
    return fd;
}

void try_exec(const char *path) {
    pid_t pid = fork();
    if (pid == 0) {
        execl(path, path, NULL);
        printf("exec %s: %s\n", path, strerror(errno));
        exit(1);
    } else {
        int st;
        waitpid(pid, &st, 0);
        if (WIFEXITED(st) && WEXITSTATUS(st)==0)
            printf("exec %s: OK\n", path);
        else
            printf("exec %s: failed (%d)\n", path, WEXITSTATUS(st));
    }
}

int main(void) {
    char pathbuf[PATH_MAX];
    char *home = getenv("HOME");

    printf("~:\n");
    system("ls -l ~");
    printf("/usr/bin (sample):\n");
    system("ls -l /usr/bin | head -n5");
    printf("/etc (sample):\n");
    system("ls -l /etc | head -n5");

    snprintf(pathbuf, sizeof(pathbuf), "%s/.profile", home);

    const char *tests[] = {
        pathbuf,
        "/bin/ls",
        "/etc/master.passwd"
    };

    for (int i = 0; i < 3; i++) {
        const char *p = tests[i];
        printf("=== %s ===\n", p);
        try_open(p, O_RDONLY);
        try_open(p, O_WRONLY|O_APPEND);
        try_exec(p);
        printf("\n");
    }

    return 0;
}
