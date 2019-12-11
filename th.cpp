#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <thread>

#include "EdgeMonitor.h"
#include "EmmisionMonitor.h"

#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"

int num_of_cars;
int num_started_cars = 0;

std::vector<std::string> paths;
std::map<std::string, int> paths_h;

std::map<std::string, EdgeMonitor*> edge_monitors;
struct args_to_thread {
    std::string path;
};
using namespace std;

void* start(void* _args) {

    cout << num_started_cars << " it comes in start" << endl;
    num_started_cars += 1;
    pthread_exit(NULL);
}
/////////////////////////////////////////////////////////////////////
void create_car_threads(pthread_t threads[]) {

    for(int i = 0; i < num_of_cars; i++) {
        struct args_to_thread* _args = new(struct args_to_thread);
        int ret = pthread_create(&threads[i], NULL, start, _args);
    }
}
////////////////////////////////////////////////////////////////////
void wait_for_threads(pthread_t threads[]) {

    for(int i = 0; i < num_of_cars; i++) {
        pthread_join(threads[i], NULL);
    }
}
////////////////////////////////////////////////////////////////////
int main() {
    num_of_cars = 1;
    pthread_t threads[num_of_cars];
    create_car_threads(threads);
    wait_for_threads(threads);
}