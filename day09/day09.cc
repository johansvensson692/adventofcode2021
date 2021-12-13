#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<size_t>> height_map;
map<pair<size_t,size_t>,bool> visited;

void
check_neighbours(pair<size_t,size_t> point,
        vector<pair<size_t,size_t>> *to_visit)
{
    for(int i = -1;i<2;i++) {
        pair<size_t,size_t> tmp;
        if (i == 0)
            continue;
        tmp = pair<size_t,size_t>(point.first+i,point.second);
        auto find_point = [point](pair<size_t,size_t> p2) {
            return point.first == p2.first && point.second == p2.second;
        };
        if (visited.count(tmp) || find_if(to_visit->begin(),to_visit->end(), find_point) != to_visit->end())
            continue;
        if(height_map[tmp.first][tmp.second] == -1 || height_map[tmp.first][tmp.second] == 9)
            continue;
        if (height_map[point.first][point.second] <
                height_map[tmp.first][tmp.second])
            to_visit->push_back(pair<size_t,size_t>(tmp));
    }
    for(int i = -1;i<2;i++) {
        pair<size_t,size_t> tmp;
        if (i == 0)
            continue;
        tmp = pair<size_t,size_t>(point.first,point.second+i);
        auto find_point = [point](pair<size_t,size_t> p2) {
            return point.first == p2.first && point.second == p2.second;
        };
        if (visited.count(tmp) || find_if(to_visit->begin(),to_visit->end(), find_point) != to_visit->end())
            continue;
        if(height_map[tmp.first][tmp.second] == -1 || height_map[tmp.first][tmp.second] == 9)
            continue;
        if (height_map[point.first][point.second] <
                height_map[tmp.first][tmp.second])
            to_visit->push_back(pair<size_t,size_t>(tmp));
    }
}

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<pair<size_t,size_t>> lowest_points;
    vector<size_t> basins;
    int part1 = 0;
    int part2 = 1;

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
        vector<size_t> tmp;
        if (height_map.size() == 0) {
            for(size_t i = 0;i<line.length()+2;i++) {
                tmp.push_back(-1);
            }
            height_map.push_back(tmp);
            tmp.clear();
        }
        tmp.push_back(-1);
        while (line.length() > 0) {
            tmp.push_back(stoi(line.substr(0,1)));
            line = line.substr(1);
        }
        tmp.push_back(-1);
        height_map.push_back(tmp);
    }
    file.close();

    vector<size_t> tmp;
    for(size_t i = 0;i<height_map[0].size();i++) {
        tmp.push_back(-1);
    }
    height_map.push_back(tmp);
    tmp.clear();

    for(size_t i = 1;i<height_map.size() - 1;i++) {
        for(size_t j = 1;j<height_map[i].size() - 1;j++) {
            if (height_map[i][j] < height_map[i-1][j] &&
                    height_map[i][j] < height_map[i][j-1] &&
                    height_map[i][j] < height_map[i][j+1] &&
                    height_map[i][j] < height_map[i+1][j]) {
                lowest_points.push_back(pair<size_t,size_t>(i,j));
                part1 += height_map[i][j] + 1;
            }
        }
    }

    for(auto it = lowest_points.begin();it != lowest_points.end();++it) {
        visited.insert(pair<pair<size_t,size_t>,bool>(*it,true));
    }

    for(auto it = lowest_points.begin();it != lowest_points.end();++it) {
        map<pair<size_t,size_t>,bool> local_basin;
        vector<pair<size_t,size_t>> to_visit;
        local_basin.insert(pair<pair<size_t,size_t>,bool>(*it,true));
        check_neighbours((*it), &to_visit);
        while (to_visit.size() > 0) {
            auto tmp = *(to_visit.begin());
            local_basin.insert(pair<pair<size_t,size_t>,bool>(tmp,true));
            visited.insert(pair<pair<size_t,size_t>,bool>(tmp,true));
            to_visit.erase(to_visit.begin());
            check_neighbours(tmp, &to_visit);
        }

        basins.push_back(local_basin.size());
    }

    sort(basins.begin(),basins.end());
    for (size_t i = 0;i<3;i++) {
        part2 *= basins.back();
        basins.pop_back();
    }


    cout << "Part 1: Sum of the low points is " << part1 << endl;
    cout << "Part 2: Product of the basins is " << part2 << endl;

    return 0;
}
