#ifndef TCP_H_
#define TCP_H_

#define SERVER 1
#define CLIENT 2

int
start_tcp
(
    int type,
	const char *ip,
	uint16_t port
);

void
listen_tcp
(
    int fd,
    char *buf,
    size_t buflen
);

void
send_tcp
(
    int fd,
    char *buf,
    size_t buflen
);

void
stop_tcp(int fd);

#endif /* TCP_H_ */