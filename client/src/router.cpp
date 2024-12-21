#include "router.hpp"
#include "config.hpp"
#include <string.h>
#include "api.hpp"

#define BUFFER_SIZE 2048

int Router::establish_connection()
{
    for (size_t i = 0; i < routing.size(); i++)
    {
        struct sockaddr_in revsockaddr;

        int sockt = socket(AF_INET, SOCK_STREAM, 0);

        revsockaddr.sin_family = AF_INET;       
        revsockaddr.sin_port = htons(BEACON_PORT);
        revsockaddr.sin_addr.s_addr = inet_addr(routing[i]);

        if (connect(sockt, (struct sockaddr *) &revsockaddr, sizeof(revsockaddr))==0) {
            return sockt;
        }
    }
    return -1;
}

void Router::server()
{
    std::thread server(run_server);
    server.detach();
}

void Router::run_server()
{
    std::cout << "[DEBUG] starting beacon server" << std::endl;
    struct sockaddr_in revsockaddr;

    int sockt = socket(AF_INET, SOCK_STREAM, 0);

    revsockaddr.sin_family = AF_INET;       
    revsockaddr.sin_port = htons(BEACON_PORT);
    revsockaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockt, (struct sockaddr*)&revsockaddr, sizeof(revsockaddr)) < 0) return;
    std::cout << "[DEBUG] Binding beacon server done" << std::endl;

    if (listen(sockt, MAX_CONNECTION) < 0) return;
    std::cout << "[DEBUG] Listen beacon server done" << std::endl;
    
    std::vector<std::thread> pool;
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(sockaddr_in);
    int new_sockt;
    
    while (true)
    {
        if ((new_sockt = accept(sockt, (sockaddr*)&client_addr, (socklen_t*)&length)) > 0) {
            std::thread t(work_client, &client_addr, new_sockt);
            pool.push_back(std::move(t));
        }
        usleep(25);
    }
}

void Router::work_client(struct sockaddr_in* client_addr, int sockt) {
    std::cout << "[SUCESS] Successfully started a new client thread" << std::endl;
    char buffer[BUFFER_SIZE];

    while (true)
    {
        memset(buffer, 0, BUFFER_SIZE);
        recv(sockt, buffer, 128, 0);
        std::cout << buffer << std::endl;

        std::string msg(buffer);

        auto request_body = json({});
        if (msg.empty()) {
            std::cerr << "[ERROR]: No data received" << std::endl;
        }
        request_body = json::parse(msg);
        std::cout << request_body << std::endl;

        try
        {
            Api api = Api::get_instance();

            std::string task_name = request_body.at("command");
            std::cout << "[DEBUG] Task received: " << task_name << std::endl;
            if (task_name == "quit") {
                std::cout << "[INFO] Client disconnected" << std::endl;
                break;
            }
            if (task_name == "get_tasks") {
                std::cout << "[INFO] Client request tasks" << std::endl;

                /* Get need data to do the API call */
                std::string uid = request_body.at("uid");
                /* Call api */
                std::string response = api.get_tasks(uid);
                /* Send the result to client */
                send(sockt, response.c_str(), response.length(), 0);

                continue;
            }
            if (task_name == "result") {
                std::cout << "[INFO] Client request tasks" << std::endl;

                /* Get need data to do the API call */
                std::string uid = request_body.at("uid");
                std::string content = request_body.at("content");
                bool code = request_body.at("code");

                /* Call api */
                std::string response = api.send_result(std::make_unique<Result>(uid, content, code));
                /* Send the result to client */
                send(sockt, response.c_str(), response.length(), 0);

                continue;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "[ERROR]: Invalid data received" << e.what() << '\n';
        }    
    }

    close(sockt);
}

void Router::client_send(int sockt, MessageRouter message) {
    /* Check that the size of the message */
    if (message.len >= BUFFER_SIZE) {
        std::cerr << "[ERROR] Canno't send data: Message too long" << std::endl;
        return;
    }

    /* Check that the socket is valid */
    if (socket < 0) {
        std::cerr << "[ERROR] Canno't send data: Invalid socket" << std::endl;
        return;
    }
    std::cout << "[DEBUG] sending data: " << message.content << std::endl;
    send(sockt, message.content, message.len, 0);
}

MessageRouter MessageFactory::create_get_tasks(std::string& uid)
{
    /* Create payload as JSON */
    boost::property_tree::ptree results_local;
    results_local.add("command", "get_tasks");
    results_local.add("uid", uid);
    std::stringstream results_string_stream;
    boost::property_tree::write_json(results_string_stream, results_local);

    std::string str = results_string_stream.str();

    int n = str.length();
    char arr[n + 1];
    std::copy(str.begin(), str.end(), arr);
    arr[n] = '\0';

    return MessageRouter(arr, str.length());
}

MessageRouter MessageFactory::create_result(std::unique_ptr<Result> results)
{
    /* Create payload as JSON */
    boost::property_tree::ptree results_local;
    results_local.add("command", "result");
    results_local.add("uid", results.get()->id);
    results_local.add("content", results.get()->content);
    results_local.add("code", results.get()->code);
    std::stringstream results_string_stream;
    boost::property_tree::write_json(results_string_stream, results_local);

    std::string msg = results_string_stream.str();

    return MessageRouter(msg.c_str(), msg.size());
}
