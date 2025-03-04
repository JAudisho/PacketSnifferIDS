import dpkt
import socket

THRESHOLD_SIZE = 1000  # Alert if a packet is larger than this

def detect_anomalies(pcap_file):
    with open(pcap_file, 'rb') as f:
        pcap = dpkt.pcap.Reader(f)
        alerts = []
        for timestamp, buf in pcap:
            eth = dpkt.ethernet.Ethernet(buf)
            ip = eth.data
            if isinstance(ip, dpkt.ip.IP):
                src = socket.inet_ntoa(ip.src)
                dst = socket.inet_ntoa(ip.dst)
                print(f"Packet: {src} -> {dst}")

                if ip.p == dpkt.ip.IP_PROTO_TCP and len(ip.data) > THRESHOLD_SIZE:
                    alert = f"ALERT: Large TCP packet detected from {src} ({len(ip.data)} bytes)"
                    print(alert)
                    alerts.append(alert)

        # Save alerts to a file
        with open("logs/alerts.log", "w") as log_file:
            for alert in alerts:
                log_file.write(alert + "\n")

if __name__ == "__main__":
    detect_anomalies("tests/test_packets.pcap")