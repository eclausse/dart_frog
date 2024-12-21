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
#include "router.hpp"

using json = nlohmann::json;

class Api
{
    private:
        Api() = default;

        inline static std::string host_="", port_="", uri_="/api/";
        inline static std::unique_ptr<Api> instance = nullptr;
        inline static Router router = Router();
        inline static int socket = -1;

        std::string send_http_post_request(std::string host,
                                        std::string port,
                                        std::string uri,
                                        std::string payload);
        std::string send_http_get_request(std::string host,
                                        std::string port,
                                        std::string uri);
        std::string send_http_file_request(std::string host,
                                        std::string port,
                                        std::string uri, 
                                        std::string path_to_file);
    public:
        ~Api() = default;

        static Api &get_instance();
        static void setup(std::string host, std::string port);

        /**
         * @brief Call /api/user/register to register the current device
         * 
         * @param uid 
         * @param name 
         * @return std::string representing JSON response 
         */
        std::string register_device(std::string uid, std::string name);

        /**
         * @brief Call /ping route and check that the response is Pong !  
         * 
         * @return true On success
         * @return false 
         */
        bool assert_ping_pong();

        /**
         * @brief Call /api/task/anyforme to get all the 
         * 
         * @param uid 
         * @return std::string representing JSON response 
         */
        std::string get_tasks(std::string uid);

        /**
         * @brief Call /api/result/add to send the result of a task
         * 
         * @param results 
         * @return std::string representing JSON response 
         */
        std::string send_result(std::unique_ptr<Result>& results);

        /**
         * @brief Call /api/file to send a file
         * 
         * @param path_to_file 
         * @return std::string 
         */
        std::string send_file(std::string path_to_file);

        /**
         * @brief Start the beacon server if we are able to contact the API
         * 
         */
        void start_server();
};
