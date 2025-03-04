#include <stdio.h>
#include <stdlib.h>
#include <pcap.h>

void packet_handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    pcap_dumper_t *dumper = (pcap_dumper_t *)user;
    pcap_dump((u_char *)dumper, h, bytes);
    printf("Packet captured: %d bytes\n", h->len);
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *dev;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Error finding devices: %s\n", errbuf);
        return 1;
    }

    dev = alldevs; // Use first available device
    printf("Using device: %s\n", dev->name);

    pcap_t *handle = pcap_open_live(dev->name, 65536, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s\n", errbuf);
        return 1;
    }

    // Open output file for writing packets
    pcap_dumper_t *dumper = pcap_dump_open(handle, "captured_packets.pcap");
    if (!dumper) {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }

    pcap_loop(handle, 10, packet_handler, (u_char *)dumper);

    pcap_dump_close(dumper);
    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return 0;
}