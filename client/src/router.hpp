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

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../includes/single_include/nlohmann/json.hpp"
using json = nlohmann::json;

#include "result.hpp"

struct MessageRouter {
    MessageRouter(const char* content, size_t len): content(content), len(len) {};
    const char* content;
    size_t len;
};

class MessageFactory
{
private:
    MessageFactory() = default;
public:
    static MessageRouter create_register_device(std::string& uid, std::string& name);
    static MessageRouter create_get_tasks(std::string& uid);
    static MessageRouter create_result(std::unique_ptr<Result>& results);
};



class Router
{
private:
    int socket_;
    inline static bool is_running = false;

    /**
     * @brief Routing service
     *        Run work_client in a separate thread for each new client
     * 
     */
    static void run_server();

    /**
     * @brief Serve a client 
     * 
     * @param client_addr 
     * @param sockt 
     */
    static void work_client(struct sockaddr_in* client_addr, int sockt);

public:
    Router() = default;
    ~Router() = default;

    /**
     * @brief Try to establish a connection to one of the routing addresses in config.hpp
     * 
     * @return int On success return the socket, otherwise -1
     */
    int establish_connection();

    /**
     * @brief Start a server service in a separate thread
     * 
     */
    void server();

    /**
     * @brief Send a serialize message through network and await the answer
     * 
     * @param message 
     */
    std::string client_send(int sockt, MessageRouter message);

    bool is_server_running();
};