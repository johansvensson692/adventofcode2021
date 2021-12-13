#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<char> stack;
    vector<string> incomplete;
    vector<size_t> scores;
    size_t part1 = 0;
    size_t part2 = 0;

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
        bool failed = false;
        for (auto it  = line.begin();it != line.end() && !failed;++it) {
            switch (*it) {
                case '(':
                /* Fallthrough */
                case '[':
                /* Fallthrough */
                case '{':
                /* Fallthrough */
                case '<':
                    stack.push_back(*it);
                    break;
                case ')':
                    if (stack.back() != '(') {
                        incomplete.push_back(line);
                        part1 += 3;
                        failed = true;
                    }
                    stack.pop_back();
                    break;
                case ']':
                    if (stack.back() != '[') {
                        incomplete.push_back(line);
                        part1 += 57;
                        failed = true;
                    }
                    stack.pop_back();
                    break;
                case '}':
                    if (stack.back() != '{') {
                        incomplete.push_back(line);
                        part1 += 1197;
                        failed = true;
                    }
                    stack.pop_back();
                    break;
                case '>':
                    if (stack.back() != '<') {
                        incomplete.push_back(line);
                        part1 += 25137;
                        failed = true;
                    }
                    stack.pop_back();
                    break;
                default:
                    cout << "???????" << endl;
                    break;
            }
            if (failed)
                break;
        }
        if (!failed) {
            part2 = 0;
            int sz_before = stack.size();
            for (size_t i = 0;i<sz_before;++i) {
                char c = stack.back();
                part2 *= 5;
                switch (c) {
                    case '(':
                        part2 += 1;
                        break;
                    case '[':
                        part2 += 2;
                        break;
                    case '{':
                        part2 += 3;
                        break;
                    case '<':
                        part2 += 4;
                        break;
                    default:
                        break;
                }
                stack.pop_back();
            }
            scores.push_back(part2);
        }
        stack.clear();
    }
    file.close();

    sort(scores.begin(),scores.end());
    
    cout << "Part 1: Syntax error score is " << part1 << endl;
    cout << "Part 2: Syntax error score is " << scores.at((scores.size() - 1) / 2) << endl;

    return 0;
}
