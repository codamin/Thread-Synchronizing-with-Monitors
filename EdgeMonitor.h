#ifndef EDGE_MONITOR
#define EDGE_MOITOR

#include <thread>
#include <semaphore.h>

class EdgeMonitor {

    private:
        sem_t mutex;
        int h;
    public:
        EdgeMonitor(int _h);
        float run(int p);
};
#endif