#include <algorithm>
#include <iostream>
#include <vector>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

bool findFile(const string& directory, const string& fileName) {
    fs::path file_path = fs::path(directory) / fileName;
    return fs::exists(file_path);
}

std::pair<std::string, std::string> processString(std::string& s) {
    std::pair<std::string, std::string> p;
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    auto it = s.find(' ');
    if (it != std::string::npos) {
        p.first = s.substr(0, it);
        p.second = s.substr(it + 1);
    } else {
        p.first = s;
    }
    return p;
}

vector<string> tokenizePath(const string& DELIMITER, string& PATH) {
    vector<string> vec;
    size_t start = 0;
    size_t end = PATH.find(DELIMITER);
    while (end != std::string::npos) {
        vec.push_back(PATH.substr(start, end - start));
        start = end + DELIMITER.length();
        end = PATH.find(DELIMITER, start);
    }
    vec.push_back(PATH.substr(start, end));
    return vec;
}

int main() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    std::string input;

    // string PATH = "/usr/bin:/usr/local/bin";
    string PATH  = getenv("PATH");

    const string DELIMITER = ":";
    vector<string> v = tokenizePath(DELIMITER, PATH);
    while (true) {
        std::cout << "$ ";
        getline(std::cin, input);
        pair<string, string> processedstring = processString(input);
        if (processedstring.first == "exit") {
            if (!processedstring.second.empty() && all_of(processedstring.second.begin(), processedstring.second.end(), ::isdigit)) {
                const int exitcode = std::stoi(processedstring.second);
                exit(exitcode);
            }
            std::cout << input << ": command not found" << std::endl;
        }

        if (processedstring.first == "echo") {
            cout << processedstring.second << endl;
        } else if (processedstring.first == "type") {
            if ( processedstring.second =="type" || processedstring.second == "exit" || processedstring.second == "echo") {
                cout << processedstring.second << " is a shell builtin\n";
            }else {
                pair<string, string> ps = processString(processedstring.second);
                if (!ps.first.empty() && ps.second.empty()) {
                    bool found = false;
                    for (const string& directorie : v) {
                        if (findFile(directorie, ps.first)) {
                            cout << ps.first << " is " << directorie << "/" << ps.first << endl;
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        cout << ps.first << ": not found" << std::endl;
                    }
                }
            }
        } else if (!input.empty()) {
            std::cout << input << ": command not found" << std::endl;
        }
    }
}