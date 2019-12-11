#include "EdgeMonitor.h"

EdgeMonitor::EdgeMonitor(int _h) {
    sem_init(&mutex, 0, 1);
    h = _h;
}

float EdgeMonitor::run(int p) {
    sem_wait(&mutex);
    float emmision;
    float divisor = p * h * 1e6;
    for(int k = 0; k < 3 * 1e8; k++) {
        emmision += k/divisor;
    }
    sem_post(&mutex);
    return emmision;
}