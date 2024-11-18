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


### Option #2: Shared Library 



