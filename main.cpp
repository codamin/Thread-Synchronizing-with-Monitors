#include "defs.h"

using namespace std;
///////////////////////////////////////////////////////////////////
vector<string> split(string line, char c)
{
    vector<string> splitted;
    string word = "";
    for(int iter = 0 ; iter < line.size() ; iter++)
    {
        if(line[iter] == c)
        {
            if(word != "")
                splitted.push_back(word);
            word = "";
        }
        else if(line[iter] != ' ')
        {
            word.push_back(line[iter]);
        }
    }
    if(word != "")
        splitted.push_back(word);

    return splitted;
}
///////////////////////////////////////////////////////////////////
string make_path(vector<string> &path_parts)
{
    string path;
    for(int i = 0; i < path_parts.size(); i++) {
        path += path_parts[i];
    }
    return path;
}
///////////////////////////////////////////////////////////////////
string make_edge(char A, char B) {
    string edge;
    edge += A;
    edge += B;
    return edge;
}
///////////////////////////////////////////////////////////////////
void read_file(vector<string> &paths, map<string, int> &paths_h) {
    fstream in_file;
    in_file.open(IN_FILE);
    
    string line;
    while(getline(in_file, line)) {
        if(line == "#")
            break;
        else {
            vector<string> parsed_line = split(line, '-');
            string new_edge = make_edge(char(parsed_line[0][0]), char(parsed_line[1][0]));
            paths_h[new_edge] = stoi(parsed_line[2]);

            //make new edge_monitor for this new_edge
            edge_monitors[new_edge] = new EdgeMonitor(paths_h[new_edge]);
        }
    }
    int path_number = 1;
    while(getline(in_file, line)) {
        vector<string> parsed_line = split(line, '-');
        string new_line = make_path(parsed_line);
        getline(in_file, line);
        int n = stoi(line);
        for(int i = 0; i < n; i++) {
            paths.push_back(new_line);
        }
        path_numbers[new_line] = path_number;
        path_number++;
    }
}
/////////////////////////////////////////////////////////////////////
void* start(void* _args) {

    //read arguments
    struct args_to_thread *args = (struct args_to_thread *)_args;
    string path = args->path;
    int thread_number = args->thread_number;

    //open new file
    ofstream new_file;
    new_file.open(string("outputs/") + to_string(path_numbers[path]) + "-" + (to_string(thread_number)).c_str());

    //send car through path
    int num_of_nodes = path.size() - 1;
    int p = rand()%10 + 1; 

    for(int i = 0; i < num_of_nodes; i++) {

        string cur_edge = make_edge(path[i], path[i + 1]);

        //write entrance node name
        new_file << path[i] << ", ";

        //write entrance time
        // new_file << std::chrono::duration_cast<std::chrono::milliseconds>
        //  (std::chrono::system_clock::now().time_since_epoch()).count() << ", ";
        
        long long emmision = edge_monitors[cur_edge]->run(new_file, p);
        emmision_monitor.add_emmision(emmision);

        //write exit node name
        new_file << path[i+1] << ", ";

        //write exit time 


        //write path emmision in file
        new_file << emmision << ", ";
        new_file << emmision_monitor.get_total_emmision();
        new_file << "\n";
    }
    new_file.close();
    pthread_exit(NULL);
}
/////////////////////////////////////////////////////////////////////
void create_car_threads(pthread_t threads[]) {

    int num_of_cars = paths.size();
    for(int i = 0; i < num_of_cars; i++) {
        struct args_to_thread* _args = new(struct args_to_thread);
        _args->path = paths[i];
        _args->thread_number = i;
        int ret = pthread_create(&threads[i], NULL, start, _args);
        if(ret != 0) {
                perror("pthread_create failed\n");
                exit(EXIT_FAILURE);
        }
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
    read_file(paths, paths_h);
    num_of_cars = paths.size();
    pthread_t threads[num_of_cars];
    create_car_threads(threads);
    wait_for_threads(threads);
}
////////////////////////////////////////////////////////////////////