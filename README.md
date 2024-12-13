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
chmod +x setup.sh
./setup.sh
```

### Execution
```bash
just
```

# Author
