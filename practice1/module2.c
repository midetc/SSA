#include <stdio.h>
#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void module2_function() {
    const char *filename = "data.txt";
    int fd = open(filename, O_RDONLY);
    if(fd == -1) {
        perror("Module2: open");
        return;
    }

    char buffer[128];
    struct aiocb cb;
    memset(&cb, 0, sizeof(struct aiocb));
    cb.aio_fildes = fd;
    cb.aio_buf = buffer;
    cb.aio_nbytes = sizeof(buffer) - 1;

    if(aio_read(&cb) == -1) {
        perror("Module2: aio_read");
        close(fd);
        return;
    }

    while(aio_error(&cb) == EINPROGRESS) {
        usleep(10000);
    }

    int ret = aio_return(&cb);
    if(ret > 0) {
        buffer[ret] = '\0';
        printf("Module2 (aio): Прочитано з файлу '%s':\n%s\n", filename, buffer);
    } else {
        perror("Module2: aio_read");
    }
    close(fd);
}
