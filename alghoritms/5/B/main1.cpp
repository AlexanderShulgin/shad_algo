#include <iostream>
#include <queue>
#include <string>
#include <vector>

const short kLL = 0;
const short kLR = 1;
const short kLN = 2;
const short kRL = 3;
const short kRR = 4;
const short kRN = 5;
const short kUL = 6;
const short kUR = 7;
const short kUN = 8;
const short kDL = 9;
const short kDR = 10;
const short kDN = 11;

struct Vertex {
    short row;
    short column;
    short code = 0;
};

void LL(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLL});
            history[vertex.row][vertex.column - 1][kLL] = {vertex.row,
                                                           vertex.column, kLL};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRL});
            history[vertex.row][vertex.column + 1][kRL] = {vertex.row,
                                                           vertex.column, kLL};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUR});
            history[vertex.row - 1][vertex.column][kUR] = {vertex.row,
                                                           vertex.column, kLL};
        }
    }
}

void LR(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLR});
            history[vertex.row][vertex.column - 1][kLR] = {vertex.row,
                                                           vertex.column, kLR};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRR});
            history[vertex.row][vertex.column + 1][kRR] = {vertex.row,
                                                           vertex.column, kLR};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDL});
            history[vertex.row + 1][vertex.column][kDL] = {vertex.row,
                                                           vertex.column, kLR};
        }
    }
}

void LN(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLN].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLN});
            history[vertex.row][vertex.column - 1][kLN] = {vertex.row,
                                                           vertex.column, kLN};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRN].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRN});
            history[vertex.row][vertex.column + 1][kRN] = {vertex.row,
                                                           vertex.column, kLN};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUR});
            history[vertex.row - 1][vertex.column][kUR] = {vertex.row,
                                                           vertex.column, kLN};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDL});
            history[vertex.row + 1][vertex.column][kDL] = {vertex.row,
                                                           vertex.column, kLN};
        }
    }
}

void RL(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLL});
            history[vertex.row][vertex.column - 1][kLL] = {vertex.row,
                                                           vertex.column, kRL};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRL});
            history[vertex.row][vertex.column + 1][kRL] = {vertex.row,
                                                           vertex.column, kRL};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDR});
            history[vertex.row + 1][vertex.column][kDR] = {vertex.row,
                                                           vertex.column, kRL};
        }
    }
}

void RR(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLR});
            history[vertex.row][vertex.column - 1][kLR] = {vertex.row,
                                                           vertex.column, kRR};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRR});
            history[vertex.row][vertex.column + 1][kRR] = {vertex.row,
                                                           vertex.column, kRR};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUL});
            history[vertex.row - 1][vertex.column][kUL] = {vertex.row,
                                                           vertex.column, kRR};
        }
    }
}

void RN(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLN].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLN});
            history[vertex.row][vertex.column - 1][kLN] = {vertex.row,
                                                           vertex.column, kRN};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRN].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRN});
            history[vertex.row][vertex.column + 1][kRN] = {vertex.row,
                                                           vertex.column, kRN};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUL});
            history[vertex.row - 1][vertex.column][kUL] = {vertex.row,
                                                           vertex.column, kRN};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDR});
            history[vertex.row + 1][vertex.column][kDR] = {vertex.row,
                                                           vertex.column, kRN};
        }
    }
}

void UL(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRR});
            history[vertex.row][vertex.column + 1][kRR] = {vertex.row,
                                                           vertex.column, kUL};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUL});
            history[vertex.row - 1][vertex.column][kUL] = {vertex.row,
                                                           vertex.column, kUL};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDL});
            history[vertex.row + 1][vertex.column][kDL] = {vertex.row,
                                                           vertex.column, kUL};
        }
    }
}

void UR(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLL});
            history[vertex.row][vertex.column - 1][kLL] = {vertex.row,
                                                           vertex.column, kUR};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUR});
            history[vertex.row - 1][vertex.column][kUR] = {vertex.row,
                                                           vertex.column, kUR};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDR});
            history[vertex.row + 1][vertex.column][kDR] = {vertex.row,
                                                           vertex.column, kUR};
        }
    }
}

void UN(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLL});
            history[vertex.row][vertex.column - 1][kLL] = {vertex.row,
                                                           vertex.column, kUN};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRR});
            history[vertex.row][vertex.column + 1][kRR] = {vertex.row,
                                                           vertex.column, kUN};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUN].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUN});
            history[vertex.row - 1][vertex.column][kUN] = {vertex.row,
                                                           vertex.column, kUN};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDN].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDN});
            history[vertex.row + 1][vertex.column][kDN] = {vertex.row,
                                                           vertex.column, kUN};
        }
    }
}

void DL(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;

    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUL});
            history[vertex.row - 1][vertex.column][kUL] = {vertex.row,
                                                           vertex.column, kDL};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDL].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDL});
            history[vertex.row + 1][vertex.column][kDL] = {vertex.row,
                                                           vertex.column, kDL};
        }
    }
    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLR});
            history[vertex.row][vertex.column - 1][kLR] = {vertex.row,
                                                           vertex.column, kDL};
        }
    }
}

void DR(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUR});
            history[vertex.row - 1][vertex.column][kUR] = {vertex.row,
                                                           vertex.column, kDR};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDR].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDR});
            history[vertex.row + 1][vertex.column][kDR] = {vertex.row,
                                                           vertex.column, kDR};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRL});
            history[vertex.row][vertex.column + 1][kRL] = {vertex.row,
                                                           vertex.column, kDR};
        }
    }
}

void DN(Vertex& vertex, std::queue<Vertex>& qwewe,
        std::vector<std::vector<char>>& matrix,
        std::vector<std::vector<std::vector<Vertex>>>& history,
        std::pair<short, short> sizes) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;

    if (vertex.column > 0) {
        if (matrix[vertex.row][vertex.column - 1] == '.' &&
            history[vertex.row][vertex.column - 1][kLR].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column - 1), kLR});
            history[vertex.row][vertex.column - 1][kLR] = {vertex.row,
                                                           vertex.column, kDN};
        }
    }
    if (vertex.column < number_of_columns - 1) {
        if (matrix[vertex.row][vertex.column + 1] == '.' &&
            history[vertex.row][vertex.column + 1][kRL].code == -1) {
            qwewe.push(
                {vertex.row, static_cast<short>(vertex.column + 1), kRL});
            history[vertex.row][vertex.column + 1][kRL] = {vertex.row,
                                                           vertex.column, kDN};
        }
    }
    if (vertex.row > 0) {
        if (matrix[vertex.row - 1][vertex.column] == '.' &&
            history[vertex.row - 1][vertex.column][kUN].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row - 1), vertex.column, kUN});
            history[vertex.row - 1][vertex.column][kUN] = {vertex.row,
                                                           vertex.column, kDN};
        }
    }
    if (vertex.row < number_of_rows - 1) {
        if (matrix[vertex.row + 1][vertex.column] == '.' &&
            history[vertex.row + 1][vertex.column][kDN].code == -1) {
            qwewe.push(
                {static_cast<short>(vertex.row + 1), vertex.column, kDN});
            history[vertex.row + 1][vertex.column][kDN] = {vertex.row,
                                                           vertex.column, kDN};
        }
    }
}

void InitialUpdateQweweAndHistory(
    std::queue<Vertex>& qwewe, std::vector<std::vector<char>>& matrix,
    Vertex begin, std::pair<short, short> sizes,
    std::vector<std::vector<std::vector<Vertex>>>& history) {
    short number_of_rows = sizes.first;
    short number_of_columns = sizes.second;
    if (begin.row > 0) {
        if (matrix[begin.row - 1][begin.column] == '.') {
            qwewe.push({static_cast<short>(begin.row - 1), begin.column, kUN});
            history[begin.row - 1][begin.column][kUN] = {begin.row,
                                                         begin.column};
        }
    }
    if (begin.row < number_of_rows - 1) {
        if (matrix[begin.row + 1][begin.column] == '.') {
            qwewe.push({static_cast<short>(begin.row + 1), begin.column, kDN});
            history[begin.row + 1][begin.column][kDN] = {begin.row,
                                                         begin.column};
        }
    }
    if (begin.column > 0) {
        if (matrix[begin.row][begin.column - 1] == '.') {
            qwewe.push({begin.row, static_cast<short>(begin.column - 1), kLN});
            history[begin.row][begin.column - 1][kLN] = {begin.row,
                                                         begin.column};
        }
    }
    if (begin.column < number_of_columns - 1) {
        if (matrix[begin.row][begin.column + 1] == '.') {
            qwewe.push({begin.row, static_cast<short>(begin.column + 1), kRN});
            history[begin.row][begin.column + 1][kRN] = {begin.row,
                                                         begin.column};
        }
    }
}

void TraceHistory(std::vector<std::vector<std::vector<Vertex>>>& history,
                  Vertex end) {
    std::vector<short> row_sequence;
    std::vector<short> column_sequence;
    while (end.code != kDN + 1) {
        row_sequence.push_back(end.row);
        column_sequence.push_back(end.column);
        end = history[end.row][end.column][end.code];
    }
    int index_max = row_sequence.size() - 1;
    for (int index = index_max; index > -1; --index) {
        std::cout << row_sequence[index] + 1 << " "
                  << column_sequence[index] + 1 << "\n";
    }
}

void UpdateQweweAndHistory(
    Vertex& vertex, std::queue<Vertex>& qwewe,
    std::vector<std::vector<char>>& matrix,
    std::vector<std::vector<std::vector<Vertex>>>& history,
    std::pair<short, short> sizes) {
    switch (vertex.code) {
        case kLL:
            LL(vertex, qwewe, matrix, history, sizes);
            break;
        case kLR:
            LR(vertex, qwewe, matrix, history, sizes);
            break;
        case kLN:
            LN(vertex, qwewe, matrix, history, sizes);
            break;
        case kRL:
            RL(vertex, qwewe, matrix, history, sizes);
            break;
        case kRR:
            RR(vertex, qwewe, matrix, history, sizes);
            break;
        case kRN:
            RN(vertex, qwewe, matrix, history, sizes);
            break;
        case kUL:
            UL(vertex, qwewe, matrix, history, sizes);
            break;
        case kUR:
            UR(vertex, qwewe, matrix, history, sizes);
            break;
        case kUN:
            UN(vertex, qwewe, matrix, history, sizes);
            break;
        case kDL:
            DL(vertex, qwewe, matrix, history, sizes);
            break;
        case kDR:
            DR(vertex, qwewe, matrix, history, sizes);
            break;
        case kDN:
            DN(vertex, qwewe, matrix, history, sizes);
            break;
    }
}

void Solve(short number_of_rows, short number_of_columns,
           std::vector<std::vector<char>>& matrix, Vertex begin, Vertex end) {
    std::vector<std::vector<std::vector<Vertex>>> history(
        number_of_rows,
        std::vector<std::vector<Vertex>>(
            number_of_columns, std::vector<Vertex>(kDN + 1, {0, 0, -1})));
    for (Vertex& vertex : history[begin.row][begin.column]) {
        vertex.code = kDN + 1;
    }

    std::queue<Vertex> qwewe;
    InitialUpdateQweweAndHistory(qwewe, matrix, begin,
                                 {number_of_rows, number_of_columns}, history);
    int level = 1;

    while (!qwewe.empty()) {
        int qwewe_size = qwewe.size();
        while (qwewe_size > 0) {
            Vertex vertex = qwewe.front();
            if (vertex.row == end.row && vertex.column == end.column) {
                std::cout << level << "\n";
                TraceHistory(history, vertex);
                return;
            }
            UpdateQweweAndHistory(vertex, qwewe, matrix, history,
                                  {number_of_rows, number_of_columns});
            qwewe.pop();
            qwewe_size--;
        }
        level++;
    }
    std::cout << -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_rows;
    short number_of_columns;
    std::cin >> number_of_rows >> number_of_columns;

    std::vector<std::vector<char>> matrix(
        number_of_rows, std::vector<char>(number_of_columns, 'a'));
    for (short row = 0; row < number_of_rows; row++) {
        for (short column = 0; column < number_of_columns; ++column) {
            std::cin >> matrix[row][column];
        }
    }
    Vertex begin;
    std::cin >> begin.row >> begin.column;
    begin.row--;
    begin.column--;
    Vertex end;
    std::cin >> end.row >> end.column;
    end.row--;
    end.column--;

    if (begin.row == end.row && begin.column == end.column) {
        std::cout << 0 << "\n";
        std::cout << begin.row + 1 << " " << begin.column + 1;
        return 0;
    }
    Solve(number_of_rows, number_of_columns, matrix, begin, end);
    return 0;
}