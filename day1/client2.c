#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_PORT 9527

void sys_err(const char *);

int main(int argc, char * argv[]) {
    char buf[BUFSIZ];
    char bufr[BUFSIZ];

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1) {
        sys_err("socket err");
    }

    int ret = connect(cfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if(ret != 0) {
        sys_err("connect err");
    }
    // while(1) {
    //     int ret = read(STDIN_FILENO, bufr, sizeof(bufr));
    //     write(cfd, bufr, ret);
    //     ret = read(cfd, buf, sizeof(buf));
    //     write(STDOUT_FILENO, buf, ret);
    //     sleep(1);
    // }
    while(1) {
        char * s = gets(bufr);
        ret = strlen(s);
        write(cfd, bufr, ret);
        ret = read(cfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        sleep(1);
    }
    close(cfd);
    return 0;
    
}

void sys_err(const char * str) {
    perror(str);
    exit(1);
}
