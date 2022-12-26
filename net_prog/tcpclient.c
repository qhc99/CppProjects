#include "etcp.h"

/**
 * stub
 * @param s
 * @param peerp
 */
static void client( SOCKET s, struct sockaddr_in *peerp )
{
    int rc;
    char buf[ 120 ];
    for ( ;; )
    {
        rc = recv( s, buf, sizeof( buf ), 0 );
        if ( rc <= 0 )
            break;
        write( 1, buf, rc );
    }
}

char *program_name;

int main(int argc, char **argv) {
    struct sockaddr_in peer;
    SOCKET s;
    INIT();
    set_address(argv[1], argv[2], &peer, "tcp");
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (!isvalidsock(s))
        error(1, errno, "socket call failed");
    if (connect(s, (struct sockaddr *) &peer,
                sizeof(peer)))
        error(1, errno, "connect failed");
    client(s, &peer);
    EXIT(0);
}