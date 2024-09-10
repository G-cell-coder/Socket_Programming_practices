#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    struct ifaddrs *ifap, *ifa;
    struct sockaddr_in *sa;
    char address[INET_ADDRSTRLEN];

    if (getifaddrs(&ifap) == -1) {
        perror("getifaddrs");
        return 1;
    }

    for (ifa = ifap; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr != NULL && ifa->ifa_addr->sa_family == AF_INET) {
            sa = (struct sockaddr_in *) ifa->ifa_addr;
            inet_ntop(AF_INET, &sa->sin_addr, address, INET_ADDRSTRLEN);
            printf("Interface: %s\n", ifa->ifa_name);
            printf("Address: %s\n", address);
        }
    }

    freeifaddrs(ifap);

    return 0;
}

