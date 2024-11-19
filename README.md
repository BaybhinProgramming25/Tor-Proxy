# Tor-Proxy-Network

TPN (Tor Proxy Network) is a tool capable of routing traffic through the tor network. Simply supply the __tpn__ keyword and any request next to it (i.e. curl, npm, etc...) and finally the destination IP address.

The program can be ran as a compiled binary or as a shared library. 

## Prerequisites

Before running the program, make sure you have the following OS and programs installed on your system

- Linux Distribtion (Debian, Ubutntu, Arch, etc...)
- Tor 
- GCC Compiler
- GNU Make
- Root Privileges (to run sudo comamnds)

## Installing GNU Make

Run the following comamnds:

```
sudo apt update && sudo apt upgrade
sudo apt install make 
```

## Installing Tor

Run the following commands:

```
sudo apt install tor
sudo systemctl start tor 
```

## Validating Tor

Run these commands to validate that tor is running on your machine 

```
netstat -tuln | grep 9050
```

9050 is the default port where tor runs on 

## Building and Running the program

### Option #1: Compiled Binary 

#### 1: Clone Repo

```
git clone <repo-url>
cd tor-proxy/src/compiled-binary
```

#### 2: Compile with make 

```
make -f compiled-binary.mk
```

Alternatively, you can also the run the __clean__ and __debug__ commands to remove previous compiled binaries and recompile the binary with debugging information, respectively. 


``` 
make clean debug -f compiled-binary.mk
```

#### 3: Run the program

The compiled binary will now be created in the __bin__ folder 

```
cd bin
```

Finally, run the program as it follows:

```
./tpn <destination-ip-address> <destination-port>
```

In the terminal, you will be presented with either one of the four status codes:
- 90: Request has been granted
- 91: Request rejected or failed  
- 92: Request rejected because SOCKS server was unable to connect to identd on the client 
- 93: Request rejected because client program and identd reported different user-ids

These response codes reflect the __SOCKS4 Protocol__. You can learn more about SOCKS4 [Here](https://www.openssh.com/txt/socks4.protocol)


### Option #2: Shared Library 

#### 1: Compile with the shared library makefile 

```
make -f shared-library.mk
```

This should create a .so (shared object) file titled __libtpn.so__ in the __build__ folder 

Note: This makefile doesn't include the extra __clean__ and __debug__ commands, which is present in the other makefile 

#### 2: Running with LD_PRELOAD

LD_PRELOAD is a environment variable that allows you to load a custom shared library before any other libraries are executed. It is essentially making it so that
whatever you defined in your program will execute first and then other libraries, if needed to be ran. 

To run the tpn command with LD_PRELOAD, type the following:

```
sudo LD_PRELOAD=./build/libtpn.so <package-manager-command> <destination-ip-address>
```

Your shared library essentially gets treated as a preloader before the application actually executes any additional libraries





