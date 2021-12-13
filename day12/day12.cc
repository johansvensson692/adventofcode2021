#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

map<string,vector<string>> connections;

bool
has_double_small_cave(vector<string> stack)
{
    map<string,bool> tmp;
    for (auto it = stack.begin();it != stack.end();++it) {
        if((*it).compare("start") == 0)
            continue;
        else if(!islower((*it).c_str()[0]))
            continue;
        if(tmp.count(*it))
            return true;
        tmp.insert(pair<string,bool>(*it,true));
    }
    return false;
}

int
visit_neighbours(string element, vector<string> stack, int max)
{
    int count = 0;
    stack.push_back(element);

    for(auto it = connections.at(element).begin();it!=connections.at(element).end();++it) {
        if((*it).compare("start") == 0)
            continue;
        if((*it).compare("end") == 0) {
            count++;
            continue;
        }
        if (islower((*it).c_str()[0])) {
            if (max == 1) {
                if(find(stack.begin(),stack.end(),(*it)) != stack.end())
                    continue;
            } else {
                if(find(stack.begin(),stack.end(),(*it)) != stack.end() && 
                    has_double_small_cave(stack))
                    continue;
            }
        }
        count += visit_neighbours((*it),stack, max);
    }
    stack.pop_back();

    return count;
}

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<string> stack;
    int part1 = 0;
    int part2 = 0;

    if (argc == 2) {
        file.open(argv[1]);
    } else {
        file.open("input.txt");
    }

    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return -1;
    }

    while (getline(file, line)) {
        int pos = line.find("-");
        string key = line.substr(0,pos);
        string value = line.substr(pos+1);
        if (!connections.count(key)) {
            vector<string> tmp;
            tmp.push_back(value);
            connections.insert(pair<string,vector<string>>(key,tmp));
        } else {
            connections.at(key).push_back(value);
        }
        if (!connections.count(value)) {
            vector<string> tmp;
            tmp.push_back(key);
            connections.insert(pair<string,vector<string>>(value,tmp));
        } else {
            connections.at(value).push_back(key);
        }
    }
    file.close();

    stack.push_back("start");
    for(auto it = connections.at("start").begin();it!=connections.at("start").end();++it) {
        part1 += visit_neighbours(*it, stack, 1);
    }

    stack.push_back("start");
    for(auto it = connections.at("start").begin();it!=connections.at("start").end();++it) {
        part2 += visit_neighbours(*it, stack, 2);
    }

    cout << "Part 1: There are " << part1 << " paths" << endl;
    cout << "Part 2: There are " << part2 << " paths" << endl;

    return 0;
}
