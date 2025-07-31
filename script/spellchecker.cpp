#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

// ------------------ Levenshtein Distance ------------------
int levenshteinDistance(const string& a, const string& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));

    for (int i = 0; i <= m; ++i) dp[i][0] = i;
    for (int j = 0; j <= n; ++j) dp[0][j] = j;

    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});

    return dp[m][n];
}

// ------------------ Command List ------------------
vector<pair<int, string>> commands_by_length = {
    {2, "bc"}, {2, "cd"}, {2, "cp"}, {2, "df"}, {2, "du"}, {2, "go"}, {2, "ip"},
    {2, "ls"}, {2, "mv"}, {2, "ps"}, {2, "rm"}, {2, "vi"}, {2, "xz"},

    {3, "apt"}, {3, "cal"}, {3, "cat"}, {3, "dig"}, {3, "dnf"}, {3, "env"}, {3, "ftp"},
    {3, "gem"}, {3, "git"}, {3, "g++"}, {3, "gcc"}, {3, "npm"}, {3, "pip"}, {3, "pwd"},
    {3, "scp"}, {3, "ssh"}, {3, "tar"}, {3, "top"}, {3, "tsc"}, {3, "vim"}, {3, "who"},
    {3, "yum"}, {3, "yes"},

    {4, "nano"}, {4, "node"}, {4, "perl"}, {4, "ping"}, {4, "pull"}, {4, "push"},
    {4, "ruby"}, {4, "stat"}, {4, "tag"}, {4, "time"}, {4, "tree"}, {4, "wget"},
    {4, "zsh"}, {4, "zip"},

    {5, "alias"}, {5, "clear"}, {5, "chmod"}, {5, "chown"}, {5, "clone"}, {5, "emacs"},
    {5, "fetch"}, {5, "find"}, {5, "merge"}, {5, "mkdir"}, {5, "mkfs"}, {5, "mount"},
    {5, "sleep"}, {5, "stash"}, {5, "touch"}, {5, "uname"}, {5, "unzip"}, {5, "watch"},
    {5, "where"}, {5, "which"}, {5, "whoami"},

    {6, "commit"}, {6, "dirname"}, {6, "fdisk"}, {6, "gedit"}, {6, "gunzip"},
    {6, "gzip"}, {6, "logout"}, {6, "source"}, {6, "status"}, {6, "telnet"},
    {6, "uptime"}, {6, "unrar"}, {6, "python"}, {6, "remote"}, {6, "rebase"},
    {6, "log"}, {6, "readlink"},

    {7, "realpath"}, {7, "flatpak"}, {7, "hostname"}, {7, "killall"}, {7, "unalias"},
    {7, "pacman"}, {7, "python3"}, {7, "rustc"}, {7, "nslookup"},

    {8, "basename"}, {8, "checkout"}, {8, "apt-get"}, {8, "branch"}, {8, "bzip2"},
    {8, "javac"}, {8, "javap"},

    {9, "traceroute"}

    
};
vector<string> twoWordCommands = {
    "git push", "git pull", "git commit", "git checkout", "git clone",
    "git status", "git add", "sudo apt", "sudo dnf", "sudo yum"
};


// ------------------ Suggest Closest Command ------------------
string suggestClosest(const string& input, int maxDistance = 2) {
    int len = input.length();
    string best = "";
    int bestDist = maxDistance + 1;

    for (const auto& [cmdLen, cmd] : commands_by_length) {
        if (cmdLen < len - 2) continue;
        if (cmdLen > len + 2) break;

        int dist = levenshteinDistance(input, cmd);
        if (dist < bestDist) {
            best = cmd;
            bestDist = dist;
        }
    }

    return best;
}

// ------------------ Main ------------------


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./spellchecker \"entire command\"\n";
        return 1;
    }

    string input = argv[1];
    stringstream ss(input);
    vector<string> words;
    string word;

    while (ss >> word) words.push_back(word);

    if (words.empty()) {
        cerr << "No command entered.\n";
        return 1;
    }

    // Combine first 2 words and compare against 2-word commands
    string correctedCmd;
    if (words.size() >= 2) {
        string combined = words[0] + " " + words[1];
        string best = "";
        int bestDist = 3;  // allow up to 2 total typos across both words

        for (const string& cmd : twoWordCommands) {
            int dist = levenshteinDistance(combined, cmd);
            if (dist < bestDist) {
                best = cmd;
                bestDist = dist;
            }
        }

        if (!best.empty()) {
            correctedCmd = best;
            words.erase(words.begin());  // remove first
            words.erase(words.begin());  // remove second
        }
    }

    // If no close 2-word command found, just fix the first word
    if (correctedCmd.empty()) {
        correctedCmd = suggestClosest(words[0]);
        words.erase(words.begin());
    }

    // Reconstruct the full command
    stringstream corrected;
    corrected << correctedCmd;
    for (const string& w : words) {
        corrected << " " << w;
    }

    cout << corrected.str() << endl;
    return 0;
}
