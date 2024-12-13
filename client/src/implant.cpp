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

}

void Implant::set_running(bool isRunning)
{
}

void Implant::service_tasks()
{
}

std::vector<Task> Implant::parse_tasks_response(const std::string &response)
{
    if(response.empty()) return std::vector<Task>();
    // Local response variable
    std::stringstream ss{ response };

    // Read response from listening post as JSON
    boost::property_tree::ptree root;
    boost::property_tree::read_json(ss, root);

    std::vector<Task> tasks;
    for (auto &task : root)
        tasks.push_back(parse_task_from_string(task.second.get<std::string>("name")));
    return tasks;
}


void test_get_tasks() {
    std::vector<Task> tasks_todo = parse_tasks_response("[{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"},{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"}]");
}