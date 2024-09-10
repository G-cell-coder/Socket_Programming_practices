#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <signal.h>

#define PACKET_SIZE     64
#define ICMP_ECHO       8
#define ICMP_REPLY      0

unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2) {
        sum += *buf++;
    }

    if (len == 1) {
        sum += *(unsigned char*)buf;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;

    return result;
}

void sendPing(const char *address) {
    struct sockaddr_in dest_addr;
    struct icmp_packet {
        struct icmphdr hdr;
        char msg[PACKET_SIZE - sizeof(struct icmphdr)];
    } packet;

    int sockfd, sent, bytes_sent;
    dest_addr.sin_family = AF_INET;
    inet_pton(AF_INET, address, &dest_addr.sin_addr);
    memset(&packet, 0, sizeof(packet));
    packet.hdr.type = ICMP_ECHO;
    packet.hdr.un.echo.id = getpid();
    packet.hdr.un.echo.sequence = 1;
    packet.hdr.checksum = checksum(&packet, sizeof(packet));

    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
   
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    sent = 0;
    bytes_sent = sendto(sockfd, &packet, sizeof(packet), 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    if (bytes_sent <= 0) {
        perror("Error sending packet");
    }

    close(sockfd);
}

void receivePing() {
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
   
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);
    struct icmp_packet {
        struct icmphdr hdr;
        char msg[PACKET_SIZE - sizeof(struct icmphdr)];
    } recv_packet;
    ssize_t bytes_received;

    while (1) {
        bytes_received = recvfrom(sockfd, &recv_packet,sizeof(recv_packet) , 0, (struct sockaddr *)&sender, &sender_len);

        if (bytes_received < 0) {
            perror("Error receiving packet");
            break;
        }

        printf("Received ICMP packet from: %s\n", inet_ntoa(sender.sin_addr));
    }

    close(sockfd);
}

void handleInterrupt(int signal) {
    printf("\nFinishing...\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <destination_ip>\n", argv[0]);
        return 1;
    }

    signal(SIGINT, handleInterrupt);

    sendPing(argv[1]);
    receivePing();

    return 0;
}

