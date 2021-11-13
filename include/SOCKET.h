
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>

#include <pthread.h>
#include <signal.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netdb.h>
#include <regex.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <sys/mman.h>

int SOCKET(int domain, int type, int protocal);
int BIND(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int LISTEN(int sockfd, int backlog);
int ACCEPT(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int CONNECT(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
