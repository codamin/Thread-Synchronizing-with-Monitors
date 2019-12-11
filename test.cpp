#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>

#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"

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
        }
    }

    while(getline(in_file, line)) {
        vector<string> parsed_line = split(line, '-');
        string new_line = make_path(parsed_line);
        getline(in_file, line);
        int n = stoi(line);
        for(int i = 0; i < n; i++) {
            paths.push_back(new_line);
        }
    }
}
////////////////////////////////////////////////////////////////////
int main() {

    vector<string> paths;
    map<string, int> paths_h;

    read_file(paths, paths_h);
    for(int i = 0; i < paths.size(); i++)
    {
        cout << paths[i] << endl;
    }
}