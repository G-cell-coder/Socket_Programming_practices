#include <stdio.h>
#include <pcap.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <string.h>

void packetHandler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    struct iphdr *ipHeader = (struct iphdr *)(packet + 14); // Skip over ethernet header
    struct sockaddr_in source;

    memset(&source, 0, sizeof(source));
    source.sin_addr.s_addr = ipHeader->saddr;

    if (ipHeader->protocol == IPPROTO_TCP) {
        printf("TCP packet from: %s\n", inet_ntoa(source.sin_addr));
    } else if (ipHeader->protocol == IPPROTO_UDP) {
        printf("UDP packet from: %s\n", inet_ntoa(source.sin_addr));
    } else if (ipHeader->protocol == IPPROTO_ICMP) {
        printf("ICMP packet from: %s\n", inet_ntoa(source.sin_addr));
    }
}

int main() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    struct bpf_program fp;
    char filter_exp[] = "ip";
    bpf_u_int32 net;
     
    if (pcap_lookupnet("wlp58s0", &net, NULL, errbuf) == -1) {
        fprintf(stderr, "Error getting network info: %s\n", errbuf);
        net = 0;
    }

    handle = pcap_open_live("wlp58s0", 65536, 1, 0, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device: %s\n", errbuf);
        return 2;
    }

    if (pcap_compile(handle, &fp, filter_exp, 0, net) == -1) {
        fprintf(stderr, "Couldn't parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
        fprintf(stderr, "Couldn't install filter %s: %s\n", filter_exp, pcap_geterr(handle));
        return 2;
    }
    pcap_loop(handle, -1, packetHandler, NULL);

    pcap_close(handle);

    return 0;
}

