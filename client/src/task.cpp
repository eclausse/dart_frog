#include "task.hpp"

Task parse_task_from_string(std::string name) {
    if (name == "ping") return PING;
    return INVALID;
}