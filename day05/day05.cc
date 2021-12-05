#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

#define GRID_SIZE 1000

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    int grid1[GRID_SIZE][GRID_SIZE];
    int grid2[GRID_SIZE][GRID_SIZE];
    int part1 = 0;
    int part2 = 0;

    memset(grid1, 0, sizeof(int) * GRID_SIZE * GRID_SIZE);
    memset(grid2, 0, sizeof(int) * GRID_SIZE * GRID_SIZE);

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
        int x1 = 0;
        int x2 = 0;
        int y1 = 0;
        int y2 = 0;
        int pos = line.find(",");
        string pos1 = line.substr(0, line.find(" "));
        x1 = stoi(pos1.substr(0,pos));
        y1 = stoi(pos1.substr(pos+1));
        string pos2 = line.substr(line.find(" ")+4);
        pos = pos2.find(",");
        x2 = stoi(pos2.substr(0,pos));
        y2 = stoi(pos2.substr(pos+1));
        int delta_x = x2 - x1;
        if (delta_x < 0)
            delta_x = -delta_x;
        int delta_y = y2 - y1;
        if (delta_y < 0)
            delta_y = -delta_y;
        if (y1 == y2) {
            if (x1 > x2) {
                int tmp = x1;
                x1 = x2;
                x2 = tmp;
            }
            for(size_t x = x1;x<=x2;x++) {
                grid1[y1][x]++;
                grid2[y1][x]++;
            }
        } else if(x1 == x2) {
            if (y1 > y2) {
                int tmp = y1;
                y1 = y2;
                y2 = tmp;
            }
            for(size_t y = y1;y<=y2;y++) {
                grid1[y][x1]++;
                grid2[y][x1]++;
            }
        } else if (delta_x == delta_y) {
            if (x1 > x2 && y1 > y2)  {
                for(size_t i = 0;i<=delta_x;i++) {
                    grid2[y1-i][x1-i]++;
                }
            } else if (x1 > x2 && y1 < y2)  {
                for(size_t i = 0;i<=delta_x;i++) {
                    grid2[y1+i][x1-i]++;
                }
            } else if (x1 < x2 && y1 > y2)  {
                for(size_t i = 0;i<=delta_x;i++) {
                    grid2[y1-i][x1+i]++;
                }
            } else if (x1 < x2 && y1 < y2)  {
                for(size_t i = 0;i<=delta_x;i++) {
                    grid2[y1+i][x1+i]++;
                }
            }
        }
    }
    file.close();

    for(size_t y = 0;y<GRID_SIZE;y++) {
        for(size_t x = 0;x<GRID_SIZE;x++) {
            cout << grid2[y][x] << " ";
            if (grid1[y][x] > 1) {
                part1++;
            }
            if (grid2[y][x] > 1) {
                part2++;
            }
        }
        cout << endl;
    }

    cout << "Part 1: " << part1 << " points overlap" << endl;
    cout << "Part 2: " << part2 << " points overlap" << endl;

    return 0;
}
