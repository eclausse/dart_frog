#include "api.hpp"


Api::Api(std::string host, std::string port): host(host), port(port), uri("/api/")
{
}

Api::~Api()
{
}

std::string Api::register_device(std::string uid, std::string name)
{   
    /* API Path */
    std::string api_uri_register = uri + "user/register";

    /* Create payload as JSON */
    boost::property_tree::ptree resultsLocal;
    resultsLocal.add("uid", uid);
    resultsLocal.add("name", name);
    std::stringstream resultsStringStream;
    boost::property_tree::write_json(resultsStringStream, resultsLocal);

    /* Send API request */
    return send_http_request(host, port, api_uri_register, resultsStringStream.str());
}

std::string Api::send_http_request(std::string host,
    std::string port,
    std::string uri,
    std::string payload) {
    // Set all our request constants
    auto const serverAddress = host;
    auto const serverPort = port;
    auto const serverUri = uri;
    auto const requestBody = json::parse(payload);

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
