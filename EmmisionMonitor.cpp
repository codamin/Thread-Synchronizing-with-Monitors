#include "EmmisionMonitor.h"

EmmisionMonitor::EmmisionMonitor() {
    float total_emmision = 0;
}

void EmmisionMonitor::add_emmision(float partial_emmision) {

    sem_wait(&mutex);
    total_emmision += partial_emmision;
    sem_post(&mutex);
}

float EmmisionMonitor::get_total_emmision() {

    return total_emmision;
}