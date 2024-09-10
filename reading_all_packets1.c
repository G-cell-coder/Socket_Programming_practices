#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

void packetHandler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct iphdr *ipHeader = (struct iphdr*)(packet + 14); // Skip over Ethernet header

    struct sockaddr_in source;
    source.sin_addr.s_addr = ipHeader->saddr;

    switch (ipHeader->protocol) {
        case IPPROTO_TCP:
            printf("TCP packet from: %s\n", inet_ntoa(source.sin_addr));
            break;
        case IPPROTO_UDP:
            printf("UDP packet from: %s\n", inet_ntoa(source.sin_addr));
            break;
        case IPPROTO_ICMP:
            printf("ICMP packet from: %s\n", inet_ntoa(source.sin_addr));
            break;
        default:
            printf("Unknown protocol packet from: %s\n", inet_ntoa(source.sin_addr));
    }
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    handle = pcap_open_live("eth0", BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s\n", errbuf);
        return 1;
    }

    if (pcap_loop(handle, 0, packetHandler, NULL) < 0) {
        fprintf(stderr, "Failed to perform packet capture: %s\n", pcap_geterr(handle));
        return 1;
    }

    pcap_close(handle);

    return 0;
}

