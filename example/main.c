#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ev.h>

#define BUFFER_SIZE 1024

void read_stdin_cb(struct ev_loop *loop, struct ev_io *watcher, int revents){
    char buffer[BUFFER_SIZE];
    ssize_t sz;

    if(EV_ERROR & revents) {
        perror("got invalid event");
        return;
    }

    // Receive message from client socket
    sz = read(watcher->fd, buffer, BUFFER_SIZE-1);
    if(sz < 0) {
        perror("read error");
        return;
    }

    if(sz == 0) {
        ev_io_stop(loop, watcher);
        free(watcher);
        perror("peer might closing");
        return;
    }

    // we read max BUFFER_SIZE-1, there is always room for '\0' at the end
    buffer[sz] = '\0';
    printf("read(size=%zd): %s", sz, buffer);

    if(strcmp(buffer, "stop\n") == 0) {
        printf("stopping loop\n");
        ev_io_stop(loop, watcher);
    }
}

int main()
{
    struct ev_loop *loop = ev_default_loop(0);
    struct ev_io w_stdin_io;

    // Initialize and start a watcher to accepts client requests
    ev_io_init(&w_stdin_io, read_stdin_cb, STDIN_FILENO, EV_READ);
    ev_io_start(loop, &w_stdin_io);

    // Start infinite loop
    printf("looping\n");
    ev_loop(loop, 0);

    printf("done\n");
    ev_loop_destroy(loop);
    return 0;
}
