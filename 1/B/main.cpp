#include <iostream>
#include <vector>

bool Open(const char& symbol) {
    return ((symbol == '[') || (symbol == '(') || (symbol == '{'));
}

bool Pair(const char& first, const char& second) {
    return (((first == '(') && (second == ')')) ||
            ((first == '[') && (second == ']')) ||
            ((first == '{') && (second == '}')));
}

void IsValid(const std::string& ss) {
    std::vector<char> stack = {};
    int counter = 0;

    for (const auto& bracket : ss) {
        if (Open(bracket)) {
            stack.push_back(bracket);
            ++counter;
        } else {
            if (stack.empty()) {
                std::cout << counter;
                return;
            }
            if (Pair(stack.back(), bracket)) {
                ++counter;
                stack.pop_back();
            } else {
                std::cout << counter;
                return;
            }
        }
    }

    if (stack.empty()) {
        std::cout << "CORRECT";
    } else {
        std::cout << ss.size();
    }
}

/*void UnitTests() {
  IsValid("(())");
  IsValid("([)]");
  IsValid("(([{");

  IsValid("(())))");
  IsValid("]())(");
  IsValid("(()){()()}");

  IsValid("");
}*/

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string input = {};
    std::cin >> input;

    IsValid(input);

    return 0;
}