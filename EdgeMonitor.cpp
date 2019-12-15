#include "EdgeMonitor.h"

EdgeMonitor::EdgeMonitor(int _h) {
    sem_init(&mutex, 0, 1);
    h = _h;
}

long long EdgeMonitor::run(int p) {
    sem_wait(&mutex);
    long long emmision = 0;
    long long divisor = p * h * 1e6;
    for(int k = 0; k <= 1e7; k++) {
        emmision += k/divisor;
    }
    sem_post(&mutex);
    return emmision;
}