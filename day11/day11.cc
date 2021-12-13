#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define NUM_ITERATIONS 100

vector<vector<int>> grid;

int
run_simulation()
{
    int count = 0;
    map<pair<size_t,size_t>,bool> visited;
    vector<pair<size_t,size_t>> to_visit;

    for(size_t y = 1;y<grid.size() - 1;y++) {
        for(size_t x = 1;x<grid[y].size() - 1;x++) {
            if (++grid[y][x] > 9) {
                count++;
                grid[y][x] = 0;
                pair<size_t,size_t> tmp (y,x);
                to_visit.push_back(tmp);
                visited.insert(pair<pair<size_t,size_t>,bool>(tmp,true));
            }
        }
    }

    while (to_visit.size() > 0) {
        pair<size_t,size_t> point = *(to_visit.begin());
        to_visit.erase(to_visit.begin());
        pair<size_t,size_t> tmp;
        for (int y = -1;y<2;++y) {
            for (int x = -1;x<2;++x) {
                if (x == 0 && y == 0)
                    continue;
                if (grid[point.first+y][point.second+x] == -1)
                    continue;
                tmp = pair<size_t,size_t>(point.first+y, point.second+x);
                if (!visited.count(tmp) &&
                        ++grid[tmp.first][tmp.second] > 9) {
                    count++;
                    grid[tmp.first][tmp.second] = 0;
                    to_visit.push_back(tmp);
                    visited.insert(pair<pair<size_t,size_t>,bool>(tmp,true));
                }
            }
        }
    }

    return count;
}


int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
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
        vector<int> tmp;
        if (grid.size() == 0) {
            for(size_t i = 0;i<line.length()+2;++i) {
                tmp.push_back(-1);
            }
            grid.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(-1);
        while (line.length() > 0) {
            int num = stoi(line.substr(0,1));
            tmp.push_back(num);
            line = line.substr(1);
        }
        tmp.push_back(-1);
        grid.push_back(tmp);
    }
    file.close();

    vector<int> tmp;
    for(size_t i = 0;i<grid[0].size();++i) {
        tmp.push_back(-1);
    }
    grid.push_back(tmp);

    for (size_t i = 0;i<NUM_ITERATIONS;++i) {
        part1 += run_simulation();
        part2++;
    }

    cout << "Part 1: Number of flashes after 100 iterations is " << part1 << endl;

    int target = (grid.size() - 2) * (grid[0].size() - 2);
    while (run_simulation() < target) {
        part2++;
    }
    part2++; // We ran the simulation but never incremented, so do that now 

    cout << "Part 2: All flahes occur simultaneously on step " << part2 <<endl;

    return 0;
}
