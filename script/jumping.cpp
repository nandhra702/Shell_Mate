#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream fin("/home/sukhaj/logger.txt");
    if (!fin) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    string line, lastLine;
    while (getline(fin, line)) {
    // Only keep lines that contain '||' and are not empty
    if (!line.empty() && line.find("||") != string::npos) {
        lastLine = line;
    }
    }

    fin.close();

    cout << "Last full line: " << lastLine << endl;

    // Check if it's a 'cd' command
    int colon_pos = lastLine.find(':');
    if (colon_pos != string::npos) {
        string command_part = lastLine.substr(colon_pos + 1);
        string checking_command = command_part.substr(0, 5);

        if (checking_command.find("cd") != string::npos) {
            cout << "Command is a cd — ignore." << endl;
            return 0;
        }
    }

    string directory=""; //LET THIS BE GLOBALLY ACCESSIBLE
    // Extract directory between || markers
    int first_delim = lastLine.find("||");
    if (first_delim == string::npos) {
        cout << "No delimiters found." << endl;
    } else {
        size_t second_delim = lastLine.find("||", first_delim + 2);
        if (second_delim != string::npos) {
            directory = lastLine.substr(first_delim + 3, second_delim - (first_delim + 3));
            cout << "Extracted directory path: [" << directory << "]" << endl;
        } else {
            cout << "Second delimiter not found." << endl;
        }
    }

    
    int current_index = 0;  //A global variables
    //perfect now I have the directory, now I need to store this directory in a vector. 
    vector<string> jump_addresses(5, "");  // size 5, all entries ""
  //we initialize a vector of a fixed size to a size of 5
    jump_addresses[current_index] = directory;
    current_index = (current_index + 1) % 5;



    return 0;
}
