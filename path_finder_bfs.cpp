#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Node {//node struct with children
    char data;//char before numbers like A1 -> A, B3 -> B
    int order;//numbers after the data like A1 -> 1, B3 -> 3
    vector<Node*> children;
    Node() {}
    Node(char _data, int _order) {
        data = _data;
        order = _order;
    }
};
vector<Node*> nodes;//holding all nodes inside
string line_arranger(string line) {//removes blanks
    string new_line = "";
    for(int i = 0; i < line.length(); i++) if(line[i] != ' ') new_line += line[i];
    return new_line;
}
bool path_finder(string path) {
    int size;
    queue<Node*> q;
    for(auto N : nodes) if(N->data == path[0]) q.push(N);//pre-process
    path = path.substr(1);
    for(auto c : path) {
        size = q.size();
        if(!size) return false;
        for(int i = 0; i < size; i++) {//mid-process
            for(auto N : q.front()->children) if(N->data == c) q.push(N);
            q.pop();
        }
    }
    return q.size();
}
int main() {
    string line;
    ifstream input("input.txt");
    ofstream output("output.txt");
    getline(input, line);
    line = line_arranger(line) + ',';
    string name = "";
    for(auto c : line) {//constructs all nodes
        if(c != ',') name += c;
        else {
            char data = name[0];
            int order = stoi(name.substr(1));
            nodes.push_back(new Node(data, order));
            name = "";
        }
    }
    getline(input, line);
    while(getline(input, line)) {//constructs all nodes->children
        line = line_arranger(line);
        if(line == "Paths:") break;
        int l_index, r_index;
        string l = line.substr(0, line.find("->"));
        for(int i = 0; i < nodes.size(); i++) 
            if(nodes[i]->data == l[0] && nodes[i]->order == stoi(l.substr(1))) l_index = i; 
        string r = line.substr(line.find("->")+2);
        for(int i = 0; i < nodes.size(); i++)
            if(nodes[i]->data == r[0] && nodes[i]->order == stoi(r.substr(1))) r_index = i;
        nodes[l_index]->children.push_back(nodes[r_index]);
    }
    while(getline(input, line)) {//finds if a path exists
        line = line_arranger(line);
        if(path_finder(line)) output << line << " " << "[YES]" << endl;
        else output << line << " " << "[NO]" << endl;
    }
    return 0;
}