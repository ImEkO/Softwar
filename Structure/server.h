#include <czmq.h>

typedef struct server Server;
struct Server {
	zsock_t *responder;
	int cmp;
}