# Packet Sniffer & Intrusion Detection System

This project captures and analyzes network packets to detect potential threats.

## Features
- Captures live packets using C and libpcap
- Detects anomalies using Python and dpkt

## Usage
```sh
gcc src/sniffer.c -o sniffer -lpcap
sudo ./sniffer
python src/detector.py tests/test_packets.pcap
