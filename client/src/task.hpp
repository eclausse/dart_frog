#pragma once

#include <string>

enum Task
{
    INVALID, PING,
};

Task parse_task_from_string(std::string);