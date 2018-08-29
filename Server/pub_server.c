#include <stdio.h>
#include <czmq.h>

int main()
{
    // create the zeromq context
    void *ctx = zctx_new();
    void *pub = zsocket_new(ctx, ZMQ_PUB);
    zsocket_connect(pub, "localhost:4242"); 
    printf("multicast initialized\n");

    while(!zctx_interrupted) {
        zstr_sendm (pub, "testing", ZMQ_SNDMORE);
        zstr_send(pub, "This is a test");
    }

    return 0;
}