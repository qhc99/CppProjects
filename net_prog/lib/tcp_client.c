//
// Created by QC on 2022-12-25.
//
#include "../etcp.h"

SOCKET tcp_client(char *hname, char *sname) {
    struct sockaddr_in peer;
    SOCKET s;
    set_address(hname, sname, &peer, "tcp");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (!isvalidsock(s))
        error(1, errno, "socket call failed");
    if (connect(s, (struct sockaddr *) &peer,
                sizeof(peer)))
        error(1, errno, "connect failed");
    return s;
}