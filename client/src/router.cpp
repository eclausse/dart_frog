#include "router.hpp"
#include "config.hpp"

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
    struct sockaddr_in revsockaddr;

    int sockt = socket(AF_INET, SOCK_STREAM, 0);

    revsockaddr.sin_family = AF_INET;       
    revsockaddr.sin_port = htons(BEACON_PORT);
    revsockaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockt, (struct sockaddr*)&revsockaddr, sizeof(revsockaddr)) < 0) return;

    if (listen(sockt, MAX_CONNECTION) < 0) return;
    
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
}