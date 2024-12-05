#include <iostream>

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;
   std::string input;
    while (true) {
        std::cout << "$ ";
        getline(std::cin, input);
        if (input == "exit 0") {
            exit(0);
            return 0;
        }
        if (!input.empty()) {
            std::cout << input << ": command not found" << std::endl;
        }
    }
}
