#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

int FindDirector(std::vector<int>& dsu, int worker_id) {
    if (dsu[worker_id] == -1) {
        return worker_id;
    }
    int root_id = worker_id;
    while (dsu[root_id] != -1) {
        root_id = dsu[root_id];
    }
    while (dsu[worker_id] != -1) {
        int parent_id = dsu[worker_id];
        dsu[worker_id] = root_id;
        worker_id = parent_id;
    }
    return root_id;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_workers;
    int number_of_queries;
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream str1(input_line);
    str1 >> number_of_workers >> number_of_queries;

    std::vector<int> dsu(number_of_workers + 1, -1);

    size_t index;
    for (int query_id = 0; query_id < number_of_queries; query_id++) {
        std::string input_line;
        std::getline(std::cin, input_line);
        index = input_line.find(' ');
        if (index == std::string::npos) {
            int worker = std::stoi(input_line);
            std::cout << FindDirector(dsu, worker) << "\n";
        } else {
            std::stringstream str(input_line);
            int boss;
            int worker;
            str >> boss >> worker;
            if (dsu[worker] == -1 && boss != worker &&
                FindDirector(dsu, boss) != worker) {
                std::cout << 1 << "\n";
                dsu[worker] = FindDirector(dsu, boss);
            } else {
                std::cout << 0 << "\n";
            }
        }
    }

    return 0;
}
