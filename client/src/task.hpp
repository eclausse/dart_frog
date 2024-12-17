#pragma once

#include <iostream>
#include <string>
#include <memory>

class Task
{
public:
    virtual ~Task() = default;
    virtual void run() = 0;
};

class PingTask: public Task
{
private:
public:
    void run() {
        std::cout << "ping" << std::endl;
    }
    ~PingTask() override {};
};

/**
 * @brief Parse a string to a task
 * If the string is not valid, return INVALID 
 * Exemple: "ping" => Task::PING
 * @return Task 
 */
std::unique_ptr<Task> parse_task_from_string(std::string);