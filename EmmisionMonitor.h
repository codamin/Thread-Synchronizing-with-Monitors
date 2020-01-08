#ifndef EMMISION_MONITOR 
#define EMMISION_MONITOR

#include <thread>
#include <semaphore.h>

class EmmisionMonitor {

    private:
        sem_t mutex;
        long long total_emmision;
    public:
        EmmisionMonitor();
        void add_emmision(long long partial_emmision);
        long long get_total_emmision();
};

#endif