#pragma once

#include "api.hpp"

#include <iostream>
#include <string>
#include <memory>

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

/**
 * @brief Parse a string to a task
 * If the string is not valid, return INVALID 
 * Exemple: "ping" => Task::PING
 * @return Task 
 */
std::unique_ptr<Task> parse_task_from_string(std::string);