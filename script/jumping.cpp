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

    

    // Check if it's a 'cd' command
    int colon_pos = lastLine.find(':');
    if (colon_pos != string::npos) {
        string command_part = lastLine.substr(colon_pos + 1);
        string checking_command = command_part.substr(0, 5);

        if (checking_command.find("cd") != string::npos) {
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
            
        } else {
            cout << "Second delimiter not found." << endl;
        }
    }

    //alright, we have the directory now, firstly, we are gonna read the contents of the file into a vector
    ifstream dir_in("/home/sukhaj/Shell_Mate/script/recent_dirs.txt");
    if (!dir_in) {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    vector<string> jump_addresses(5);  // Fixed-size vector with 5 empty strings
int flag = 0; // Flag to indicate if directory already exists
string directory_file_line;
int vec_count = 0;

// Read existing non-empty lines into the vector
while (getline(dir_in, directory_file_line)) {
    if (!directory_file_line.empty()) {
        if (directory_file_line == directory) {
            flag = 1;
        }
        if (vec_count < 5) {
            jump_addresses[vec_count++] = directory_file_line;
        }
    }
}

dir_in.close();

if (flag == 0) {
    // Address doesn't exist, insert using circular overwrite
    jump_addresses[vec_count % 5] = directory;
}

// Now, write back to file
ofstream fout("/home/sukhaj/Shell_Mate/script/recent_dirs.txt");
for (int i = 0; i < 5; i++) {
    if (!jump_addresses[i].empty()) {
        fout << jump_addresses[i] << '\n';
    }
}
fout.close();

    
    
     return 0;
}
