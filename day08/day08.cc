#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> decoded_outputs;

void
decode_output(vector<string> signals, vector<string> outputs)
{
    map<char,char> keys;
    map<string,size_t> dec;

    /* Find a - the difference between 7 and 1 */
    auto seven = *find_if(signals.begin(), signals.end(), [] (string s) { return s.length() == 3; });
    auto one = *find_if(signals.begin(), signals.end(), [] (string s) { return s.length() == 2; });
    for(auto it = seven.begin();it != seven.end();++it) {
        if (one.find(*it) == string::npos) {
            keys.insert(pair<char,char>('a',*it));
            break;
        }
    }
    dec.insert(pair<string,size_t>(seven,7));
    dec.insert(pair<string,size_t>(one,1));

    /* Find g - the difference between 9 and 4. 9 contains 4 + a, which we know already */
    auto four = *find_if(signals.begin(), signals.end(), [] (string s) { return s.length() == 4; });
    auto eight = *find_if(signals.begin(), signals.end(), [] (string s) { return s.length() == 7; });
    dec.insert(pair<string,size_t>(four,4));
    dec.insert(pair<string,size_t>(eight,8));
    for(auto it = signals.begin();it != signals.end();++it) {
        if ((*it).length() == 6) {
            int count = 0;
            for(auto jt = four.begin();jt != four.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    break;
                }
                count++;
            }
            if (count < 4) {
                continue;
            }
            dec.insert(pair<string,size_t>(*it,9));
            string s;
            for(auto jt = (*it).begin();jt != (*it).end();++jt) {
                if (four.find(*jt) == string::npos &&
                    *jt != keys.at('a')) {
                    s.push_back(*jt);
                }
            }
            keys.insert(pair<char,char>('g',s[0]));
            s.clear();
        }
    }

    /* Find d - the difference between 8 and 0. We can eliminate 9 and 0 contains all of 7 */
    for(auto it = signals.begin();it != signals.end();++it) {
        if ((*it).length() == 6) {
            int count = 0;
            for(auto jt = four.begin();jt != four.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    break;
                }
                count++;
            }
            if (count == 4) {
                continue;
            }
            count = 0;
            for(auto jt = seven.begin();jt != seven.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    break;
                }
                count++;
            }
            if (count < 3) {
                continue;
            }
            dec.insert(pair<string,size_t>(*it,0));
            string s;
            for(auto jt = eight.begin();jt != eight.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    s.push_back(*jt);
                }
            }
            keys.insert(pair<char,char>('d',s[0]));
            s.clear();
        }
    }

    /* Find 6 - it is length 6 and is not 9 and 0 */
    for(auto it = signals.begin();it != signals.end();++it) {
        if ((*it).length() == 6) {
            if (!dec.count(*it)) {
                dec.insert(pair<string,size_t>(*it,6));
                break;
            }
        }
    }

    /* Find e - the difference between 9 and 8. */
    for(auto it = signals.begin();it != signals.end();++it) {
        if ((*it).length() == 6) {
            int count = 0;
            for(auto jt = four.begin();jt != four.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    break;
                }
                count++;
            }
            if (count < 4) {
                continue;
            }
            string s;
            for(auto jt = eight.begin();jt != eight.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    s.push_back(*jt);
                }
            }
            keys.insert(pair<char,char>('e',s[0]));
            s.clear();
        }
    }

    /* Find 3 - it is length 5 and contains 1 */
    for(auto it = signals.begin();it != signals.end();++it) {
        if ((*it).length() == 5) {
            int count = 0;
            for(auto jt = one.begin();jt != one.end();++jt) {
                if ((*it).find(*jt) == string::npos) {
                    break;
                }
                count++;
            }
            if (count < 2) {
                continue;
            }
            dec.insert(pair<string,size_t>(*it,3));
        }
    }

    /* Find 3 - it is length 5, contains e, and is not 3 */
    for(auto it = signals.begin();it != signals.end();++it) {
        if (dec.count(*it) == 1 ||
            (*it).find(keys.at('e')) == string::npos) {
            continue;
        }
        dec.insert(pair<string,size_t>(*it,2));
    }

    /* Find 2 - it is the only one not in dec */
    for(auto it = signals.begin();it != signals.end();++it) {
        if (dec.count(*it) == 1)
            continue;
        dec.insert(pair<string,size_t>(*it,5));
    }

    /* Decode output */
    string output;
    for (auto it = outputs.begin();it != outputs.end();++it) {
        string tmp = *it;
        sort(tmp.begin(),tmp.end());
        string s = std::to_string(dec.at(tmp));
        output.push_back(s.c_str()[0]);
    }

    decoded_outputs.push_back(stoi(output));
}

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<string> signals;
    vector<string> outputs;
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
        for(size_t i = 0;i<10;i++) {
            int pos = line.find(" ");
            string tmp = line.substr(0,pos);
            sort(tmp.begin(),tmp.end());
            signals.push_back(tmp);
            line = line.substr(pos+1);
        }
        line = line.substr(2);
        for(size_t i = 0;i<4;i++) {
            int pos = line.find(" ");
            string tmp = line.substr(0,pos);
            sort(tmp.begin(),tmp.end());
            outputs.push_back(tmp);
            switch (line.substr(0,pos).length()) {
                case 2:
                case 3:
                case 4:
                case 7:
                    part1++;
                    break;
                default:
                    break;
            }
            line = line.substr(pos+1);
        }
        decode_output(signals,outputs);
        signals.clear();
        outputs.clear();
    }
    file.close();

    cout << "Part 1: Digits 1, 4, 7, and 8 appears " << part1 << " times" << endl;

    for(auto it = decoded_outputs.begin();it != decoded_outputs.end();++it) {
        part2 += *it;
    }

    cout << "Part 2: Sum of decoded values is " << part2 << endl;

    return 0;
}
