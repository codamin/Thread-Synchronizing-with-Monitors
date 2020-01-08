#include "EdgeMonitor.h"

using namespace std;

EdgeMonitor::EdgeMonitor(int new_h) {
    h = new_h;
    sem_init(&mutex, 0, 1);
}

long long EdgeMonitor::run(ofstream &new_file, int p) {
    sem_wait(&mutex);

    new_file << std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count() << ", ";

    long long emmision = 0;
    long long divisor = p * h * 1e6;
    for(int k = 0; k <= 1e7; k++) {
        emmision += k/divisor;
    }

    new_file << std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::system_clock::now().time_since_epoch()).count() << ", ";

    sem_post(&mutex);
    return emmision;
}