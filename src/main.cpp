#include <algorithm>
#include <iostream>
using namespace std;

std::pair<std::string,std::string> processString(std::string& s) {
    std::pair<std::string, std::string> p;
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    auto it  = s.find(' ');
    if (it != std::string::npos) {
        p.first = s.substr(0, it);
        p.second = s.substr(it + 1);
    } else {
        p.first = s;
    }
    return p;
}
int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
   std::string input;
    while (true) {
        std::cout << "$ ";
        getline(std::cin, input);
        if (input == "exit 0") {
            exit(0);
        }
        pair<string, string> processedstring = processString(input);
        if (processedstring.first == "echo") {
            cout << processedstring.second<<endl;
        }else if (processedstring.first == "type") {
            pair<string, string> ps = processString(processedstring.second);
            if (ps.first == "echo" || ps.first == "exit" || ps.first == "type") {
                cout << ps.first << " is a shell builtin" <<endl;
            }else {
                std::cout << processedstring.second << ": not found" << std::endl;
            }
        }else if (!input.empty()) {
            std::cout << input << ": command not found" << std::endl;
        }
    }
}


