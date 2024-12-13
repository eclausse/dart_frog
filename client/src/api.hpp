#pragma once

#include <iostream>
#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../includes/single_include/nlohmann/json.hpp"

#include <cpr/cpr.h>
#include "result.hpp"

using json = nlohmann::json;

class Api
{
    private:
        const std::string host, port, uri;
        std::string send_http_request(std::string host,
                                        std::string port,
                                        std::string uri,
                                        std::string payload);
    public:
        Api(std::string host, std::string port);
        ~Api();
        std::string register_device(std::string uid, std::string name);
        //std::string get_tasks(std::string uid);
        std::string send_result(std::unique_ptr<Result> results);
};
