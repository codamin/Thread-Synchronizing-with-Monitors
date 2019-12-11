#ifndef EMMISION_MONITOR 
#define EMMISION_MONITOR

#include <thread>
#include <semaphore.h>

class EmmisionMonitor {

    private:
        sem_t mutex;
        float total_emmision;
    public:
        EmmisionMonitor();
        void add_emmision(float partial_emmision);
        float get_total_emmision();
};

#endif