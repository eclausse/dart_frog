#include "task.hpp"
#include <memory>

std::unique_ptr<Task> parse_task_from_string(std::string name) {
    if (name == "ping") {
        return std::make_unique<PingTask>();
    }
    return nullptr;
}