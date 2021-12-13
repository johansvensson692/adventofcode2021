#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define GRID_SIZE_X 1500
#define GRID_SIZE_Y 1500

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<vector<int>> grid;
    vector<pair<char,int>> fold;
    int grid_x = -1;
    int grid_y = -1;
    int part1 = 0;

    for(size_t i = 0;i<GRID_SIZE_Y;++i) {
        vector<int> tmp;
        tmp.resize(GRID_SIZE_X, 0);
        grid.push_back(tmp);
    }

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
        if (line.length() == 0)
            continue;
        int pos = line.find(",");
        if (pos != string::npos) {
            int x = stoi(line.substr(0,pos));
            int y = stoi(line.substr(pos+1));
            grid[y][x]++;
            x++;
            y++;
            if(x > grid_x)
                grid_x = x;
            if(y > grid_y)
                grid_y = y;
        } else {
            line = line.substr(11);
            int tmp = stoi(line.substr(2));
            fold.push_back(pair<char,int>(line.c_str()[0],tmp));
        }
    }
    file.close();

    grid.resize(grid_y);
    for(size_t y = 0;y<grid.size();++y) {
        grid[y].resize(grid_x);
    }

    for(auto it = fold.begin();it != fold.end();++it) {
        if ((*it).first == 'y') {
            int fold_line = (*it).second;
            for(size_t y = 0; y < fold_line;y++) {
                for(size_t x = 0;x < grid[y].size();++x) {
                    grid[y][x] += grid[grid.size() - 1 - y][x];
                }
            }
            int tmp = grid.size();
            for(size_t y = fold_line; y < tmp;y++) {
                grid.pop_back();
            }
        } else if ((*it).first == 'x') {
            int fold_line = (*it).second;
            for(size_t y = 0; y < grid.size();++y) {
                for(size_t x = 0;x < fold_line;++x) {
                    grid[y][x] += grid[y][grid[y].size() - 1 - x];
                }
            }
            for(size_t y = 0; y < grid.size();++y) {
                int tmp = grid[y].size();
                for(size_t x = fold_line; x < tmp;x++) {
                    grid[y].pop_back();
                }
            }
        } else {
            cout << "Unknown value????" << endl;
        }

        if (part1 == 0) {
            for(size_t y = 0;y<grid.size();++y) {
                for(size_t x = 0;x<grid[y].size();++x) {
                    if(grid[y][x])
                        part1++;
                }
            }
        }
    }

    cout << "Part 1: After first fold " << part1 << " dots are visible" << endl;

    cout << "Part 2: The infrared thermal imaging camera code is: " << endl;
    for(size_t y = 0;y<grid.size();++y) {
        for(size_t x = 0;x<grid[y].size();++x) {
            cout << (grid[y][x] ? "#" : ".");
        }
        cout << endl;
    }

    return 0;
}
