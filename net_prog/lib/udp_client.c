//
// Created by QC on 2022-12-26.
//
#include "../etcp.h"

SOCKET udp_client(char *hname, char *sname,
                  struct sockaddr_in *sap) {
    SOCKET s;
    set_address(hname, sname, sap, "udp");
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (!isvalidsock(s))
        error(1, errno, "socket call failed");
    return s;
}