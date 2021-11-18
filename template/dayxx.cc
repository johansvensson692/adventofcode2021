#include <iostream>
#include <fstream>

using namespace std;

int
main(int argc, char *argv[])
{
    ifstream file;
    string line;

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
        cout << line << endl;
    }
    file.close();

    return 0;
}
