#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    size_t epsilon = 0;
    size_t gamma = 0;
    size_t generator_rating = 0;
    size_t scrubber_rating = 0;
    map<size_t,size_t> ones;
    map<size_t,size_t> zeroes;
    vector<string> scrubber;
    vector<string> generator;

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
        scrubber.push_back(line);
        generator.push_back(line);
        for (size_t i = 0;i<line.length();++i) {
            if (line[i] == '1') {
                ones[i] = ones[i] + 1;
            } else if (line[i] == '0') {
                zeroes[i] = zeroes[i] + 1;
            }
        }
    }
    file.close();

    for (size_t i = 0;i<ones.size();++i) {
        if (ones[i] >= zeroes[i]) {
            gamma += (1 << (ones.size() - i - 1));
        } else {
            epsilon += (1 << (ones.size() - i - 1));
        }
    }

    cout << "Part 1: The power consumption is " << gamma * epsilon << endl;
    for (size_t i = 0;i<ones.size();i++) {
        int ones = 0;
        int zeroes = 0;
        for (auto it = generator.begin();it != generator.end();it++) {
            if ((*it)[i] == '1') {
                ones++;
            } else {
                zeroes++;
            }
        }
        vector<string> tmp;
        if (ones >= zeroes) {
            for(auto it = generator.begin();it != generator.end();++it) {
                if ((*it)[i] == '1') {
                    tmp.push_back(*it);
                }
            }
            generator.swap(tmp);
            tmp.clear();
        } else {
            for(auto it = generator.begin();it != generator.end();++it) {
                if ((*it)[i] == '0') {
                    tmp.push_back(*it);
                }
            }
            generator.swap(tmp);
            tmp.clear();
        }
        if (generator.size()  == 1)
            break;
    }

    for (size_t i = 0;i<ones.size();i++) {
        int ones = 0;
        int zeroes = 0;
        for (auto it = scrubber.begin();it != scrubber.end();it++) {
            if ((*it)[i] == '1') {
                ones++;
            } else {
                zeroes++;
            }
        }
        vector<string> tmp;
        if (ones >= zeroes) {
            for(auto it = scrubber.begin();it != scrubber.end();++it) {
                if ((*it)[i] == '0') {
                    tmp.push_back(*it);
                }
            }
            scrubber.swap(tmp);
            tmp.clear();
        } else {
            for(auto it = scrubber.begin();it != scrubber.end();++it) {
                if ((*it)[i] == '1') {
                    tmp.push_back(*it);
                }
            }
            scrubber.swap(tmp);
            tmp.clear();
        }
        if (scrubber.size()  == 1)
            break;
    }

    string tmp = generator.at(0);
    for (size_t i = 0;i<tmp.length();++i) {
        if (tmp[i] == '1')
            generator_rating += 1 << (tmp.length() - i - 1);
    }
    tmp = scrubber.at(0);
    for (size_t i = 0;i<tmp.length();++i) {
        if (tmp[i] == '1')
            scrubber_rating += 1 << (tmp.length() - i - 1);
    }

    cout << "Part 2: The life support rating is " << generator_rating * scrubber_rating << endl;

    return 0;
}
