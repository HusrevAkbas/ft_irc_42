# pragma once

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <ctime>
#include <stdexcept>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/epoll.h>
#include <sys/types.h>

#include <fcntl.h>

#include <errno.h>

#define	GREEN	"\e[3;32m"
#define	YELLOW	"\e[3;33m"
#define	RESET	"\e[0m"