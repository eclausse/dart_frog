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
#include <memory>
#include <algorithm>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "api.hpp"
#include "task.hpp"

class Implant {
    public:
        Implant();

        /* Implant entry point */
        void beacon();

    private:
        std::string id;
        bool is_running;
        std::vector<std::unique_ptr<Task>> tasks;

        /**
         * @brief Utility to parse a std::string JSON response to a vector of Task
         * 
         * @param response 
         * @return std::vector<Task> 
         */
        void parse_tasks_response(const std::string &response);

        void run_all();

        void test_get_tasks();
};
