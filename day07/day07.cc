#include <climits>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<int> numbers;
    int minimum_distance = INT_MAX;
    int minimum_idx = -1;
    int biggest = 0;
    int smallest = INT_MAX;

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
    int pos = line.find(",");
    while (pos != string::npos) {
        pos = line.find(",");
        numbers.push_back(stoi(line.substr(0,pos)));
        line = line.substr(pos+1);
    }

    for (auto it = numbers.begin();it != numbers.end();++it) {
        if (*it < smallest) {
            smallest = *it;
        }
        if (*it > biggest) {
            biggest = *it;
        }
    }

    for (size_t i = smallest;i<biggest;i++) {
        int distance = 0;
        for (auto it = numbers.begin();it != numbers.end();++it) {
            int tmp = *it - i;
            if (tmp < 0)
                tmp = -tmp;
            distance += tmp;
        }
        if (distance < minimum_distance) {
            minimum_distance = distance;
            minimum_idx = i;
        }
    }

    cout << "Part 1: Position " << minimum_idx << " has minimum fuel " << minimum_distance << endl;

    minimum_distance = INT_MAX;
    minimum_idx = -1;
    for (size_t i = smallest;i<biggest;i++) {
        int distance = 0;
        for (auto it = numbers.begin();it != numbers.end();++it) {
            int tmp = *it - i;
            int sum = 0;
            if (tmp < 0)
                tmp = -tmp;
            for(size_t j = 0;j<tmp;++j) {
                sum += j+1;
            }
            distance += sum;
        }
        if (distance < minimum_distance) {
            minimum_distance = distance;
            minimum_idx = i;
        }
    }

    cout << "Part 2: Position " << minimum_idx << " has minimum fuel " << minimum_distance << endl;

    return 0;
}
