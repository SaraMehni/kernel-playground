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

## Project Results

The module was successfully compiled and loaded into the Linux kernel.

The Netfilter hook detects IPv4 localhost packets (127.0.0.1) and prints their source and destination addresses using printk.

The module was tested by generating localhost traffic with:

```bash
ping 127.0.0.1
```

The expected output was observed in the kernel log using:

```bash
dmesg
```

## Implementation Notes

The project is implemented as a Linux kernel module using the Netfilter framework.

The hook function checks whether both the source and destination IP addresses are 127.0.0.1.

If a localhost packet is detected, the module logs the packet information and accepts the packet without modifying it.
