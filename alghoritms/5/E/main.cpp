#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
const int kMaxInt = 2000000000;

std::vector<int> GenerateMasks(int number_of_rows, int number_of_columns,
                               int number_of_edges) {
    std::vector<int> masks;
    masks.reserve(number_of_edges);
    if (number_of_rows > 1) {
        int begin = (1 << number_of_columns) + 1;
        int end =
            (1 << (number_of_rows * number_of_columns - 1)) +
            (1 << (number_of_rows * number_of_columns - number_of_columns - 1));
        for (int help = begin; help <= end; help = help << 1) {
            masks.push_back(help);
        }
    }

    if (number_of_columns > 1) {
        int mask = 3;
        for (int _ = 0; _ < number_of_rows; _++) {
            for (int _ = 1; _ < number_of_columns; _++) {
                masks.push_back(mask);
                mask = mask << 1;
            }
            mask = mask << 1;
        }
    }
    return masks;
}

int GenerateChess(int number_of_rows, int number_of_columns) {
    int chess = 0;
    for (int row = 0; row < number_of_rows; row++) {
        if (row % 2 == 0) {
            for (int column = 0; column < number_of_columns; column += 2) {
                chess += (1 << (number_of_columns * row + column));
            }
        } else {
            for (int column = 1; column < number_of_columns; column += 2) {
                chess += (1 << (number_of_columns * row + column));
            }
        }
    }
    return chess;
}

void Solve(int initial, int number_of_rows, int number_of_columns) {
    int number_of_vertices = 1 << (number_of_rows * number_of_columns);
    int number_of_edges = 2 * number_of_rows * number_of_columns -
                          number_of_rows - number_of_columns;

    int first_chess = GenerateChess(number_of_rows, number_of_columns);
    int second_chess =
        ((1 << (number_of_rows * number_of_columns)) - 1) ^ first_chess;
    if (initial == first_chess || initial == second_chess) {
        std::cout << 0;
        return;
    }

    std::vector<int> masks =
        GenerateMasks(number_of_rows, number_of_columns, number_of_edges);

    std::vector<char> visited(number_of_vertices, ' ');

    int distance_to_first_chess = kMaxInt;
    int distance_to_second_chess = kMaxInt;

    std::queue<int> qwewe;
    qwewe.push(initial);
    int level = 0;

    while (!qwewe.empty()) {
        int qwewe_size = qwewe.size();
        while (qwewe_size > 0) {
            int vertex = qwewe.front();
            if (vertex == first_chess) {
                distance_to_first_chess = level;
            }
            if (vertex == second_chess) {
                distance_to_second_chess = level;
            }

            for (int mask : masks) {
                int next_vertex = vertex ^ mask;
                if (visited[next_vertex] == ' ') {
                    visited[next_vertex] = 'y';
                    qwewe.push(next_vertex);
                }
            }
            qwewe.pop();
            qwewe_size--;
        }
        level++;
    }

    int answer = std::min(distance_to_first_chess, distance_to_second_chess);
    if (answer == kMaxInt) {
        std::cout << -1 << "\n";
    } else {
        std::cout << answer << "\n";
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_rows;
    int number_of_columns;
    std::cin >> number_of_rows >> number_of_columns;
    if (number_of_rows == 1 && number_of_columns == 1) {
        std::cout << 0;
        return 0;
    }
    std::string initial_string{};
    for (int _ = 0; _ < number_of_rows; ++_) {
        std::string row;
        std::cin >> row;
        initial_string += row;
    }
    int initial = std::stoi(initial_string, 0, 2);
    Solve(initial, number_of_rows, number_of_columns);
    return 0;
}