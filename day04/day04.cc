#include <map>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

static bool 
check_board(vector<vector<int>> bingo)
{
    for (size_t j = 0;j<5;j++){
        int count_hs = 0;
        int count_vt = 0;
        for (size_t i = 0;i<5;i++){
            if (bingo[j][i]) {
                count_hs++;
            }
            if (bingo[i][j]) {
                count_vt++;
            }
        }
        if (count_hs == 5 || count_vt == 5)
            return true;
    }

    return false;
}

static int
count_unmarked(vector<vector<int>> board, vector<vector<int>> bingo)
{
    int sum = 0;

    for (size_t j = 0;j<5;j++){
        for (size_t i = 0;i<5;i++){
            if (!bingo[j][i]) {
                sum += board[j][i];
            }
        }
    }

    return sum;
}

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;
    vector<size_t> numbers;
    vector<vector<vector<int>>> boards;
    vector<vector<vector<int>>> bingo;
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

    getline(file,line);
    int pos = line.find(",");
    while(pos != string::npos) {
        pos =  line.find(",");
        int num = stoi(line.substr(0, pos));
        line = line.substr(pos+1);
        numbers.push_back(num);
    }

    while (getline(file,line)) {
        vector<vector<int>> tmp;
        for (size_t j = 0;j<5;j++){
            getline(file, line);
            vector<int> tmp2;
            for(size_t i = 0;i<5;i++) {
                int number = stoi(line.substr(0, 2));
                tmp2.push_back(number);
                if (i < 4)
                    line = line.substr(3);
            }
            tmp.push_back(tmp2);
        }
        boards.push_back(tmp);
        vector<vector<int>> tmp3;
        for (size_t i = 0;i<5;i++){
            vector<int> tmp4;
            for (size_t j = 0;j<5;j++){
                tmp4.push_back(0);
            }
            tmp3.push_back(tmp4);
        }
        bingo.push_back(tmp3);
    }
    file.close();

    int found_winner = 0;
    map<int,int> winners;
    for (auto it = numbers.begin();it != numbers.end();++it) {
        for (size_t h = 0;h<boards.size();h++){
            if(winners.count(h))
                continue;
            for (size_t j = 0;j<5;j++){
                for(size_t i = 0;i<5;i++) {
                    if ((*it) == boards[h][j][i]) {
                        bingo[h][j][i] = 1;
                    }
                }
            }
            if (check_board(bingo[h])) {
                winners.insert(pair<int,int>(h, 1));
                if (!part1)
                    part1 = count_unmarked(boards[h], bingo[h]) * (*it);
                found_winner++;
                if (found_winner == boards.size()) {
                    cout << (*it) << endl;
                    part2 = count_unmarked(boards[h], bingo[h]) * (*it);
                    break;
                }
            }
        }
        if (part2)
            break;
    }

    cout << "Part 1: The sum is " << part1 << endl;
    cout << "Part 2: The sum is " << part2 << endl;

    return 0;
}
