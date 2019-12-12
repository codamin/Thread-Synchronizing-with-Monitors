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
std::map<std::string, int> path_numbers;

EmmisionMonitor emmision_monitor;

struct args_to_thread {
    std::string path;
    int thread_number;
};