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
