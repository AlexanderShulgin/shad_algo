#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct Point {
    int i = 0;
    int j = 0;
    int limit = -1;   // left,right
    int number = -1;  // left,right,up,down
    bool operator==(Point point) const { return i == point.i && i == point.i; }
    bool operator!=(Point point) const { return j != point.j || j != point.j; }
};

void LeftToRight(  // NOLINT
    Point& current_place, std::queue<Point>& neighbours,
    std::vector<std::vector<char>>& field,
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>>& visited) {
    int column_number = field[0].size();
    if (current_place.j < column_number - 1 &&
        field[current_place.i][current_place.j + 1] == '.') {
        if (current_place.number == 0 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j + 1][0].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 0, 0});
            visited[current_place.i][current_place.j + 1][0].first =
                current_place;
        }
        if (current_place.number == 0 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j + 1][0].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 1, 0});
            visited[current_place.i][current_place.j + 1][0].second =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j + 1][0].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 0, 0});
            visited[current_place.i][current_place.j + 1][0].first =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j + 1][0].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 1, 0});
            visited[current_place.i][current_place.j + 1][0].second =
                current_place;
        }
        if (current_place.number == 2 && current_place.limit == 0) {
        }
        if (current_place.number == 2 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j + 1][0].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 0, 0});
            visited[current_place.i][current_place.j + 1][0].first =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j + 1][0].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j + 1, 1, 0});
            visited[current_place.i][current_place.j + 1][0].second =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j + 1][0].second.limit ==
                -1) {
        }
    }
}

void RightToLeft(  // NOLINT
    Point& current_place, std::queue<Point>& neighbours,
    std::vector<std::vector<char>>& field,
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>>& visited) {
    int column_number = field[0].size();
    if (current_place.j > 0 &&
        field[current_place.i][current_place.j - 1] == '.') {
        if (current_place.number == 0 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j - 1][1].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 0, 1});
            visited[current_place.i][current_place.j - 1][1].first =
                current_place;
        }
        if (current_place.number == 0 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j - 1][1].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 1, 1});
            visited[current_place.i][current_place.j - 1][1].second =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j - 1][1].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 0, 1});
            visited[current_place.i][current_place.j - 1][1].first =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j - 1][1].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 1, 1});
            visited[current_place.i][current_place.j - 1][1].second =
                current_place;
        }
        if (current_place.number == 2 && current_place.limit == 1) {
        }
        if (current_place.number == 2 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j - 1][1].second.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 1, 1});
            visited[current_place.i][current_place.j - 1][1].second =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j - 1][1].first.limit ==
                -1) {
            neighbours.push({current_place.i, current_place.j - 1, 0, 1});
            visited[current_place.i][current_place.j - 1][1].first =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j + 1][0].second.limit ==
                -1) {
        }
    }
}

void DownToUp(  // NOLINT
    Point& current_place, std::queue<Point>& neighbours,
    std::vector<std::vector<char>>& field,
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>>& visited) {
    int string_number = field.size();
    if (current_place.i > 0 &&
        field[current_place.i - 1][current_place.j] == '.') {
        if (current_place.number == 0 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j - 1][1].first.limit ==
                -1) {
        }
        if (current_place.number == 0 && current_place.limit == 1 &&
            visited[current_place.i - 1][current_place.j][3].first.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 0, 3});
            visited[current_place.i - 1][current_place.j][3].first =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 0 &&
            visited[current_place.i - 1][current_place.j][3].second.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 1, 3});
            visited[current_place.i - 1][current_place.j][3].second =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 1 &&
            visited[current_place.i][current_place.j - 1][1].second.limit ==
                -1) {
        }
        if (current_place.number == 2 && current_place.limit == 0 &&
            visited[current_place.i - 1][current_place.j][3].first.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 0, 3});
            visited[current_place.i - 1][current_place.j][3].first =
                current_place;
        }
        if (current_place.number == 2 && current_place.limit == 1 &&
            visited[current_place.i - 1][current_place.j][3].second.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 1, 3});
            visited[current_place.i - 1][current_place.j][3].second =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 0 &&
            visited[current_place.i - 1][current_place.j][3].first.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 0, 3});
            visited[current_place.i - 1][current_place.j][3].first =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 1 &&
            visited[current_place.i - 1][current_place.j][3].second.limit ==
                -1) {
            neighbours.push({current_place.i - 1, current_place.j, 1, 3});
            visited[current_place.i - 1][current_place.j][3].second =
                current_place;
        }
    }
}

void UpToDown(  // NOLINT
    Point& current_place, std::queue<Point>& neighbours,
    std::vector<std::vector<char>>& field,
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>>& visited) {
    int string_number = field.size();
    if (current_place.i < string_number - 1 &&
        field[current_place.i + 1][current_place.j] == '.') {
        if (current_place.number == 0 && current_place.limit == 0 &&
            visited[current_place.i + 1][current_place.j][2].second.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 1, 2});
            visited[current_place.i + 1][current_place.j][2].second =
                current_place;
        }
        if (current_place.number == 0 && current_place.limit == 1 &&
            visited[current_place.i - 1][current_place.j][3].first.limit ==
                -1) {
        }
        if (current_place.number == 1 && current_place.limit == 1 &&
            visited[current_place.i + 1][current_place.j][2].first.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 0, 2});
            visited[current_place.i + 1][current_place.j][2].first =
                current_place;
        }
        if (current_place.number == 1 && current_place.limit == 0 &&
            visited[current_place.i][current_place.j - 1][1].second.limit ==
                -1) {
        }
        if (current_place.number == 2 && current_place.limit == 0 &&
            visited[current_place.i + 1][current_place.j][2].first.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 0, 2});
            visited[current_place.i + 1][current_place.j][2].first =
                current_place;
        }
        if (current_place.number == 2 && current_place.limit == 1 &&
            visited[current_place.i + 1][current_place.j][2].second.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 1, 2});
            visited[current_place.i + 1][current_place.j][2].second =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 0 &&
            visited[current_place.i + 1][current_place.j][2].first.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 0, 2});
            visited[current_place.i + 1][current_place.j][2].first =
                current_place;
        }
        if (current_place.number == 3 && current_place.limit == 1 &&
            visited[current_place.i + 1][current_place.j][2].second.limit ==
                -1) {
            neighbours.push({current_place.i + 1, current_place.j, 1, 2});
            visited[current_place.i + 1][current_place.j][2].second =
                current_place;
        }
    }
}

void ReconstructWay(
    std::vector<Point>& way,
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>>& visited,
    Point begin, Point end) {
    Point current_point = end;
    while (current_point != begin) {
        way.push_back(current_point);
        if (current_point.limit == 0) {
            current_point =
                visited[current_point.i][current_point.j][current_point.number]
                    .first;
        } else {
            current_point =
                visited[current_point.i][current_point.j][current_point.number]
                    .second;
        }
    }
    way.push_back(begin);
}

std::vector<Point> FindWay(Point begin, Point end,
                           std::vector<std::vector<char>>& field,
                           int string_number, int column_number) {
    std::queue<Point> neighbours;
    std::vector<std::vector<std::vector<std::pair<Point, Point>>>> visited(
        string_number,
        std::vector<std::vector<std::pair<Point, Point>>>(
            column_number, std::vector<std::pair<Point, Point>>(4)));
    std::vector<Point> way;

    // int fast = FirstStep(begin, end, field, neighbours, visited);
    for (int number = 0; number < 4; number++) {
        neighbours.push({begin.i, begin.j, 0, number});
        visited[begin.i][begin.j][begin.number].first = {begin.i, begin.j, 0,
                                                         0};
    }
    for (int number = 0; number < 4; number++) {
        neighbours.push({begin.i, begin.j, 1, number});
        visited[begin.i][begin.j][begin.number].second = {begin.i, begin.j, 0,
                                                          0};
    }
    bool flag = false;
    while (!neighbours.empty()) {
        Point current_place = neighbours.front();
        neighbours.pop();
        if (current_place == end) {
            flag = true;
            break;
        }
        LeftToRight(current_place, neighbours, field, visited);
        RightToLeft(current_place, neighbours, field, visited);
        DownToUp(current_place, neighbours, field, visited);
        UpToDown(current_place, neighbours, field, visited);
    }
    if(flag){
        ReconstructWay(way, visited, begin, end);
        return way;
    }
    return std::vector<Point>();
}

int main() {
    int string_number = 0;
    int column_number = 0;

    std::cin >> string_number >> column_number;

    std::vector<std::vector<char>> field(string_number,
                                         std::vector<char>(column_number));

    for (int i = 0; i < string_number; ++i) {
        for (int j = 0; j < column_number; ++j) {
            std::cin >> field[i][j];
        }
    }

    Point begin;
    std::cin >> begin.i >> begin.j;
    begin.i--;
    begin.j--;
    Point end;
    std::cin >> end.i >> end.j;
    end.i--;
    end.j--;
    if (begin == end) {
        std::cout << 0 << "\n";
        std::cout << begin.i << " " << begin.j;
        return 0;
    }
    std::vector<Point> way =
        FindWay(begin, end, field, string_number, column_number);

    if (way.empty()) {
        std::cout << "-1" << '\n';
    } else {
        std::cout << way.size() - 1 << '\n';
        for (int index = static_cast<int>(way.size() - 1); index >= 0;
             --index) {
            std::cout << way[index].i << " " << way[index].j << '\n';
        }
    }

    return 0;
}