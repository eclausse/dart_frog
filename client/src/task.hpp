#pragma once

#include <string>

enum Task
{
    INVALID, PING,
};

/**
 * @brief Parse a string to a task
 * If the string is not valid, return INVALID 
 * Exemple: "ping" => Task::PING
 * @return Task 
 */
Task parse_task_from_string(std::string);