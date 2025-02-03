#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> seq;
    int a;
    std::cin >> a;
    seq.push_back(a);

    for (int k = 1; k < n; ++k) {
        std::cin >> a;
        if (a != seq.back()) {
            seq.push_back(a);
        }
    }

    if (seq.size() == 1) {
        std::cout << seq.front();
        return 0;
    }

    std::vector<int> extr;
    extr.push_back(0);
    for (size_t i = 1; i + 1 < seq.size(); ++i) {
        if (((seq[i] > seq[i - 1]) && (seq[i] > seq[i + 1])) ||
            ((seq[i] < seq[i - 1]) && (seq[i] < seq[i + 1]))) {
            extr.push_back(i);
        }
    }
    extr.push_back(seq.size() - 1);

    std::cout << seq[extr.front()] << "\n";

    int previous = seq[extr[0]];
    size_t counter = 0;

    if (seq[extr[0]] < seq[extr[1]]) {
        while (counter + 2 < extr.size()) {
            if (counter % 2 == 0) {
                int temp = extr[counter];
                while (temp <= extr[counter + 1]) {
                    if ((seq[temp] > previous) &&
                        (seq[temp] > seq[extr[counter + 2]])) {
                        std::cout << seq[temp] << "\n";
                        previous = seq[temp];
                        break;
                    } else {
                        ++temp;
                    }
                }
            } else {
                int temp = extr[counter];
                while (temp <= extr[counter + 1]) {
                    if ((seq[temp] < previous) &&
                        (seq[temp] < seq[extr[counter + 2]])) {
                        std::cout << seq[temp] << "\n";
                        previous = seq[temp];
                        break;
                    } else {
                        ++temp;
                    }
                }
            }
            ++counter;
        }

        if (counter % 2 == 0) {
            int temp = extr[counter];
            while (temp <= extr[counter + 1]) {
                if (seq[temp] > previous) {
                    std::cout << seq[temp] << "\n";
                    break;
                } else {
                    ++temp;
                }
            }
        } else {
            int temp = extr[counter];
            while (temp <= extr[counter + 1]) {
                if (seq[temp] < previous) {
                    std::cout << seq[temp] << "\n";
                    break;
                } else {
                    ++temp;
                }
            }
        }
    } else {
        while (counter + 2 < extr.size()) {
            if (counter % 2 == 1) {
                int temp = extr[counter];
                while (temp <= extr[counter + 1]) {
                    if ((seq[temp] > previous) &&
                        (seq[temp] > seq[extr[counter + 2]])) {
                        std::cout << seq[temp] << "\n";
                        previous = seq[temp];
                        break;
                    } else {
                        ++temp;
                    }
                }
            } else {
                int temp = extr[counter];
                while (temp <= extr[counter + 1]) {
                    if ((seq[temp] < previous) &&
                        (seq[temp] < seq[extr[counter + 2]])) {
                        std::cout << seq[temp] << "\n";
                        previous = seq[temp];
                        break;
                    } else {
                        ++temp;
                    }
                }
            }
            ++counter;
        }

        if (counter % 2 == 1) {
            int temp = extr[counter];
            while (temp <= extr[counter + 1]) {
                if (seq[temp] > previous) {
                    std::cout << seq[temp] << "\n";
                    break;
                } else {
                    ++temp;
                }
            }
        } else {
            int temp = extr[counter];
            while (temp <= extr[counter + 1]) {
                if (seq[temp] < previous) {
                    std::cout << seq[temp] << "\n";
                    break;
                } else {
                    ++temp;
                }
            }
        }
    }

    return 0;
}