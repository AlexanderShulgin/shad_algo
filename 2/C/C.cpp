#include <array>
#include <iostream>
#include <vector>

void MergeCurrentPair(int& current_size, int& current_pair, int& from, int& to,
                      std::array<std::vector<int>, 2>& scratches) {
    int lp = 2 * current_size * current_pair;
    int rp = lp + current_size;
    int lp_end = rp;
    int rp_end = lp_end + current_size;
    while ((lp < lp_end) && (rp < rp_end)) {
        if (scratches[from][lp] <= scratches[from][rp]) {
            scratches[to].push_back(scratches[from][lp]);
            ++lp;
        } else {
            scratches[to].push_back(scratches[from][rp]);
            ++rp;
        }
    }
    if (lp == lp_end) {
        while (rp < rp_end) {
            scratches[to].push_back(scratches[from][rp]);
            ++rp;
        }
    } else {
        while (lp < lp_end) {
            scratches[to].push_back(scratches[from][lp]);
            ++lp;
        }
    }
}

void MergeLastPair(int& current_size, int& current_n_seq, int& from, int& to,
                   std::array<std::vector<int>, 2>& scratches) {
    int rp = (current_n_seq - 1) * current_size;
    int rp_end = scratches[from].size();
    int lp = rp - current_size;
    int lp_end = rp;
    while ((lp < lp_end) && (rp < rp_end)) {
        if (scratches[from][lp] <= scratches[from][rp]) {
            scratches[to].push_back(scratches[from][lp]);
            ++lp;
        } else {
            scratches[to].push_back(scratches[from][rp]);
            ++rp;
        }
    }
    if (lp == lp_end) {
        while (rp < rp_end) {
            scratches[to].push_back(scratches[from][rp]);
            ++rp;
        }
    } else {
        while (lp < lp_end) {
            scratches[to].push_back(scratches[from][lp]);
            ++lp;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n_seq;
    int n_elem;
    std::cin >> n_seq >> n_elem;

    std::array<std::vector<int>, 2> scratches;
    scratches[0].reserve(n_seq * n_elem);
    scratches[1].reserve(n_seq * n_elem);
    for (int ii = 0; ii < n_seq; ++ii) {
        for (int jj = 0; jj < n_elem; ++jj) {
            int element;
            std::cin >> element;
            scratches[0].push_back(element);
        }
    }

    int current_n_seq = n_seq;
    int current_size = n_elem;
    int epoch = 0;

    while (current_n_seq != 1) {
        int from = epoch % 2;
        int to = 0;
        if (from == 0) {
            to = 1;
        }

        for (int current_pair = 0; current_pair < ((current_n_seq - 1) / 2);
             ++current_pair) {
            MergeCurrentPair(current_size, current_pair, from, to, scratches);
        }

        if (current_n_seq % 2 != 0) {
            int pointer_end = scratches[from].size();
            for (int pointer = (current_n_seq - 1) * current_size;
                 pointer < pointer_end; ++pointer) {
                scratches[to].push_back(scratches[from][pointer]);
            }
        } else {
            MergeLastPair(current_size, current_n_seq, from, to, scratches);
        }
        current_size *= 2;
        current_n_seq = current_n_seq / 2 + current_n_seq % 2;
        epoch += 1;
        scratches[from].clear();
    }

    for (const int& elem : scratches[epoch % 2]) {
        std::cout << elem << " ";
    }

    return 0;
}