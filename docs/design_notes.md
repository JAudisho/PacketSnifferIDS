# Design Notes for Packet Sniffer & IDS

## Architecture Overview
The system has two main parts:
- **Packet Sniffer (C program)** using `libpcap` (Npcap on Windows) to capture raw network packets.
- **Intrusion Detection (Python script)** analyzing packet captures for anomalies.

## Design Decisions
- **Packet Capture**: Uses `Npcap` as a Windows-compatible `libpcap` alternative.
- **Intrusion Detection**: A simple rule-based system flags large TCP packets.
- **Storage**: Captured packets are saved to a `.pcap` file for later analysis in Wireshark.

## Possible Improvements
- Implement deeper packet inspection (e.g., detecting specific attack patterns).
- Add real-time alerts via email or Slack.
- Use machine learning models for anomaly detection.

## Challenges Faced
- Ensuring compatibility with Windows (Npcap vs. libpcap).
- Handling large amounts of network data efficiently.

## Testing Strategy
- Capture test packets with Wireshark and run the IDS to check alert generation.
- Introduce simulated attack traffic and validate detection accuracy.