#pragma once

#include <thread>
#include <vector>
#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Router
{
private:
    int socket_;
public:
    Router() = default;
    ~Router() = default;

    /**
     * @brief Try to establish a connection to one of the routing addresses in config.hpp
     * 
     * @return int On success return the socket, otherwise -1
     */
    int establish_connection();

    void server();
    void run_server();
    void work_client(struct sockaddr_in* client_addr, int sockt);
};