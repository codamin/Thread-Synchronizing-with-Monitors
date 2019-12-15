#include "EmmisionMonitor.h"

EmmisionMonitor::EmmisionMonitor() {
    total_emmision = 0;
    sem_init(&mutex, 0, 1);
}

void EmmisionMonitor::add_emmision(long long partial_emmision) {

    sem_wait(&mutex);
    total_emmision += partial_emmision;
    sem_post(&mutex);
}

long long EmmisionMonitor::get_total_emmision() {

    return total_emmision;
}