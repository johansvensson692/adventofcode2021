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
    vector<int> window;
    int last_num;
    int count1 = 0;
    int count2 = 0;

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
        numbers.push_back(stoi(line));
    }
    file.close();

    last_num = numbers[0];
    for (size_t i = 1;i<numbers.size();++i) {
        if (numbers[i] > last_num) {
            ++count1;
        }
        last_num = numbers[i];
    }

    cout << "Task 1: " << count1 << " measurements were larger than the previous" << endl;

    window.push_back(numbers[0]);
    window.push_back(numbers[1]);
    window.push_back(numbers[2]);
    for (size_t i = 3;i<numbers.size();++i) {
        int new_sum = 0;
        int old_sum = 0;
        for (auto iter = window.begin();iter !=window.end();++iter) {
            old_sum += *iter;
        }

        window.erase(window.begin());
        window.push_back(numbers[i]);
        for (auto iter = window.begin();iter !=window.end();++iter) {
            new_sum += *iter;
        }
        if (new_sum > old_sum) {
            count2++;
        }
    }

    cout << "Task 2: " << count2 << " three-measurements were larger than the previous" << endl;

    return 0;
}
