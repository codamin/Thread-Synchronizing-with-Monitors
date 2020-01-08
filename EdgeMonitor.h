#ifndef EDGE_MONITOR
#define EDGE_MOITOR

#include <thread>
#include <semaphore.h>
#include <fstream>

class EdgeMonitor {

    private:
        sem_t mutex;
        int h;
    public:
        EdgeMonitor(int _h);
        long long run(char c, std::ofstream &new_file, int p);
};
#endif