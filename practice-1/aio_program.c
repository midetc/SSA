#include <stdio.h>
#include <aio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
    const char* filename = "test.txt";
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    struct aiocb cb;
    memset(&cb, 0, sizeof(cb));
    cb.aio_fildes = fd;
    cb.aio_buf = buffer;
    cb.aio_nbytes = sizeof(buffer) - 1;
    cb.aio_offset = 0;

    if (aio_read(&cb) == -1) {
        perror("aio_read");
        close(fd);
        return 1;
    }

    while (aio_error(&cb) == EINPROGRESS);

    int ret = aio_return(&cb);
    if (ret > 0) {
        buffer[ret] = '\0';
        printf("Прочитано %d байт: %s\n", ret, buffer);
    } else {
        printf("Не вдалося прочитати дані або сталася помилка.\n");
    }

    close(fd);
    return 0;
}
