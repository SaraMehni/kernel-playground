# M5 - Localhost Traffic Monitor

This project implements a Linux kernel module that monitors localhost IPv4 traffic using the Netfilter framework.

## Usage

The directory contains a Makefile to build the module.

### Build

```bash
make
```

### Install

```bash
sudo insmod monitor.ko
```

### Test

```bash
ping 127.0.0.1
dmesg
```

### Remove

```bash
sudo rmmod monitor
```

## Files

- monitor.c : Linux kernel module source
- Makefile : Build configuration
- README.md : Project documentation

## Author

Sara Mehni

Course: Software Networks

Assignment: M5 - Localhost Traffic Monitor

## Description

This kernel module monitors localhost IPv4 traffic using the Netfilter framework.
It detects IPv4 packets sent to and from the localhost address (127.0.0.1) and prints the source and destination IP addresses to the kernel log.

### Example Output

```text
Localhost Packet: 127.0.0.1 -> 127.0.0.1
```
