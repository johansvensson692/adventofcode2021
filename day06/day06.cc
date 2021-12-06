#include <map>
#include <iostream>
#include <fstream>

using namespace std;

auto constexpr part1_iterations = 80;
auto constexpr part2_iterations = 256;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    map<size_t,size_t> fish;

    if (argc == 2) {
        file.open(argv[1]);
    } else {
        file.open("input.txt");
    }

    if (!file.is_open()) {
        cerr << "File is not open!" << endl;
        return -1;
    }

    getline(file, line);
    file.close();

    int pos = 0;
    while (pos != string::npos) {
        pos = line.find(",");
        size_t tmp = stoi(line.substr(0,pos));
        if (fish.count(tmp)) {
            fish[tmp]++;
        } else {
            fish.insert(pair<size_t,size_t>(tmp,1));
        }
        line = line.substr(pos+1);
    }

    for(size_t j = 0;j<=8;j++) {
        if (!fish.count(j)) {
            fish.insert(pair<size_t,size_t>(j,0));
        }
    }

    for (size_t i = 0;i<part2_iterations;i++) {
        map<size_t,size_t> tmp;
        size_t born = 0;
        for(size_t j = 0;j<=8;j++) {
            tmp.insert(pair<size_t,size_t>(j,0));
        }

        tmp[6] += fish[0];
        born += fish[0];
        for(size_t j = 1;j<=8;j++) {
            tmp[j-1] += fish[j];
        }
        tmp[8] += born;
        if (i == part1_iterations) {
            size_t sum = 0;
            for(auto it = fish.begin();it != fish.end();++it) {
                sum += (*it).second;
            }
            cout << "Part 1: There are " << sum << " lanternfish" << endl;
        }
        tmp.swap(fish);
        tmp.clear();
    }

    size_t sum = 0;
    for(auto it = fish.begin();it != fish.end();++it) {
        sum += (*it).second;
    }
    cout << "Part 2: There are " << sum << " lanternfish" << endl;

    return 0;
}
