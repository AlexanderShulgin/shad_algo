#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct HorizontalSide {
    HorizontalSide(short ls, short rs, short yc, bool dn, short nmbr)
        : left_side(ls),
          right_side(rs),
          y_coordinate(yc),
          down(dn),
          number(nmbr) {}
    short left_side;
    short right_side;
    short y_coordinate;
    bool down;
    short number;
};

struct Input {
    int x_range;
    int y_range;
    short number_of_rectangulars;
};

struct Color {
    Color(short number, short color_number) {
        map = std::vector<short>(number, 0);
        area = std::vector<int>(color_number, 0);
    }
    std::vector<short> map;
    std::vector<int> area;
};

void FillColumn(std::vector<HorizontalSide>& lines, Color& color, Input input,
                std::priority_queue<short>& heap,
                std::pair<short, short> cur_next_pivot) {
    short current_pivot = cur_next_pivot.first;
    short next_pivot = cur_next_pivot.second;
    short width = next_pivot - current_pivot;
    short height;
    short lines_size = static_cast<short>(lines.size());
    short current_y = 0;
    short line_index = 0;
    while (line_index < lines_size) {
        if (lines[line_index].left_side > current_pivot ||
            lines[line_index].right_side < next_pivot) {
            line_index++;
            continue;
        }
        break;
    }
    if (line_index == lines_size) {
        color.area[1] += input.y_range * (next_pivot - current_pivot);
        return;
    }
    std::vector<char> was_deleted(input.number_of_rectangulars + 1, 'f');
    short last_meaningful_y;
    current_y = lines[line_index].y_coordinate;
    if (current_y != 0) {
        color.area[1] +=
            static_cast<int>(lines[line_index].y_coordinate) * width;
    }
    while (line_index < lines_size) {
        if (lines[line_index].left_side > current_pivot ||
            lines[line_index].right_side < next_pivot) {
            line_index++;
            continue;
        }
        last_meaningful_y = lines[line_index].y_coordinate;
        if (lines[line_index].y_coordinate == current_y) {
            if (lines[line_index].down) {
                heap.push(lines[line_index].number);
            } else {
                was_deleted[lines[line_index].number] = 't';
            }
            line_index++;
        } else {
            height = lines[line_index].y_coordinate - current_y;
            while (was_deleted[heap.top()] == 't') {
                heap.pop();
            }
            color.area[color.map[heap.top()]] +=
                static_cast<int>(height) * width;
            current_y = lines[line_index].y_coordinate;
        }
    }
    while (heap.size() > 1) {
        heap.pop();
    }
    color.area[1] +=
        static_cast<int>((input.y_range - last_meaningful_y)) * width;
}

void FillColorAreas(std::vector<HorizontalSide>& lines, Color& color,
                    Input input, std::vector<short>& pivots) {
    short current_pivot;
    short next_pivot;
    short pivots_size = static_cast<short>(pivots.size());

    std::priority_queue<short> heap;
    heap.push(0);

    for (short next_pivot_index = 1; next_pivot_index < pivots_size;
         next_pivot_index++) {
        current_pivot = pivots[next_pivot_index - 1];
        next_pivot = pivots[next_pivot_index];
        FillColumn(lines, color, input, heap, {current_pivot, next_pivot});
    }
    color.area[1] +=
        input.y_range * (pivots.front() + input.x_range - pivots.back());
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const short kColorNumber = 2500;
    Input input;
    std::cin >> input.x_range >> input.y_range >> input.number_of_rectangulars;

    Color color(input.number_of_rectangulars + 1, kColorNumber + 1);
    color.map[0] = 1;

    std::vector<HorizontalSide> lines;
    lines.reserve(input.number_of_rectangulars * 2);
    std::vector<short> uncompressed_pivots;
    uncompressed_pivots.reserve(input.number_of_rectangulars * 2);

    short llx;
    short lly;
    short urx;
    short ury;
    short color_name;
    for (short number = 1; number <= input.number_of_rectangulars; ++number) {
        std::cin >> llx >> lly >> urx >> ury >> color_name;
        if (llx == urx || lly == ury) {
            continue;
        }
        color.map[number] = color_name;
        uncompressed_pivots.push_back(llx);
        uncompressed_pivots.push_back(urx);
        lines.emplace_back(llx, urx, ury, false, number);
        lines.emplace_back(llx, urx, lly, true, number);
    }
    if (lines.empty()) {
        std::cout << 1 << " " << input.x_range * input.y_range;
        return 0;
    }
    std::sort(lines.begin(), lines.end(),
              [](HorizontalSide& side1, HorizontalSide& side2) {
                  return side1.y_coordinate < side2.y_coordinate;
              });

    std::sort(uncompressed_pivots.begin(), uncompressed_pivots.end());
    std::vector<short> pivots;
    pivots.reserve(input.number_of_rectangulars * 2);
    pivots.push_back(uncompressed_pivots.front());
    for (short& pivot : uncompressed_pivots) {
        if (pivot == pivots.back()) {
            continue;
        }
        pivots.push_back(pivot);
    }

    FillColorAreas(lines, color, input, pivots);
    for (short color_index = 1; color_index <= kColorNumber; color_index++) {
        if (color.area[color_index] != 0) {
            std::cout << color_index << " " << color.area[color_index] << "\n";
        }
    }

    return 0;
}