#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

typedef enum {
    FORWARD,
    UP,
    DOWN,
} dir_t;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<pair<dir_t,int>> instructions;
    int horizontal_pos = 0;
    int depth_pos = 0;
    int aim = 0;

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
        int split_pos = line.find(" ");
        string dir = line.substr(0, split_pos);
        int dist = stoi(line.substr(split_pos+1));
        if (dir.compare("up") == 0) {
            instructions.push_back(make_pair(UP,dist));
        } else if (dir.compare("down") == 0) {
            instructions.push_back(make_pair(DOWN,dist));
        } else if (dir.compare("forward") == 0) {
            instructions.push_back(make_pair(FORWARD,dist));
        }
    }
    file.close();

    for (auto iter = instructions.begin();iter != instructions.end();++iter) {
        switch ((*iter).first) {
            case FORWARD:
                horizontal_pos += (*iter).second;
                break;
            case UP:
                depth_pos += (*iter).second;
                break;
            case DOWN:
                depth_pos -= (*iter).second;
                break;
            default:
                cout << "Invalid value: " << (*iter).first << endl;
        }
    }

    cout << "Part 1: Horizontal position multipled with depth is " << horizontal_pos * ((depth_pos < 0) ? -depth_pos : depth_pos) << endl;

    horizontal_pos = 0;
    depth_pos = 0;

    for (auto iter = instructions.begin();iter != instructions.end();++iter) {
        switch ((*iter).first) {
            case FORWARD:
                horizontal_pos += (*iter).second;
                depth_pos += aim * (*iter).second;
                break;
            case UP:
                aim += (*iter).second;
                break;
            case DOWN:
                aim -= (*iter).second;
                break;
            default:
                cout << "Invalid value: " << (*iter).first << endl;
        }
    }

    cout << "Part 2: Horizontal position multipled with depth is " << horizontal_pos * ((depth_pos < 0) ? -depth_pos : depth_pos) << endl;

    return 0;
}
