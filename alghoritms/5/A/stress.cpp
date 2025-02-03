#include <error.h>

#include <iostream>
#include <random>
#include <vector>

std::vector<short> GenRandomArray(std::mt19937* gen, size_t count, int from,
                                  int to) {
    std::uniform_int_distribution<int> dist(from, to);
    std::vector<short> data(count);
    for (auto& cur : data) {
        cur = dist(*gen);
    }
    return data;
}

struct VertexEdges {
    std::vector<short> incoming;
    std::vector<short> outcoming;
};

void DFS(short vertex_number, std::vector<VertexEdges>& vertices,
         std::vector<char>& colors,
         std::vector<short>& topological_ordered_vertices,
         bool& there_is_no_cycles) {
    colors[vertex_number] = 'g';
    for (short future_vertex : vertices[vertex_number].outcoming) {
        if (colors[future_vertex] == 'g') {
            there_is_no_cycles = false;
        }
        if (colors[future_vertex] == 'w') {
            DFS(future_vertex, vertices, colors, topological_ordered_vertices,
                there_is_no_cycles);
        }
    }
    colors[vertex_number] = 'b';
    topological_ordered_vertices.push_back(vertex_number);
}

void BDFS(short vertex_number, std::vector<VertexEdges>& vertices,
          std::vector<char>& colors, short& component_number,
          std::vector<short>& vertex_component) {
    colors[vertex_number] = 'b';
    vertex_component[vertex_number] = component_number;
    for (short future_vertex : vertices[vertex_number].incoming) {
        if (colors[future_vertex] == 'w') {
            BDFS(future_vertex, vertices, colors, component_number,
                 vertex_component);
        }
    }
}

void StressTest() {
    std::mt19937 generator(72874);             // NOLINT
    for (int iter = 1; iter <= 10000; ++iter) {  // NOLINT
        std::cerr << "Test " << iter << "... ";
        short number_of_people;
        short number_of_games;
        auto array = GenRandomArray(&generator, 2, 1, 50000);  // NOLINT
        number_of_people = array[0];
        number_of_games = array[1];
        std::cout<<"NUMBER OF PEOPLE: "<<number_of_people<<"\n";
        std::cout<<"NUMBER OF GAMES: "<<number_of_games<<"\n";
        std::vector<VertexEdges> vertices(number_of_people);
        std::cerr << "МИЛЯ КАМЕНЬ1\n";
        auto first =
            GenRandomArray(&generator, number_of_games, 1, number_of_people);
        std::cerr << "МИЛЯ КАМЕНЬ2\n";
        auto second =
            GenRandomArray(&generator, number_of_games, 1, number_of_people);
        auto third = GenRandomArray(&generator, number_of_games, 1, 3);
        for (short _ = 0; _ < number_of_games; _++) {
            short first_player = first[_];
            short second_player = second[_];
            short winner = third[_];
            ///
            if (first_player == second_player) {
                continue;
            }

            if (winner == 3) {
                continue;
            }
            first_player--;
            second_player--;
            if (winner == 1) {
                vertices[first_player].outcoming.push_back(second_player);
                vertices[second_player].incoming.push_back(first_player);
            } else {
                vertices[first_player].incoming.push_back(second_player);
                vertices[second_player].outcoming.push_back(first_player);
            }
        }
        if (number_of_people == 1) {
            // std::cout << 1;
            // return 0;
            continue;
        }
        std::vector<char> colors(number_of_people, 'w');
        std::vector<short> topological_ordered_vertices;
        topological_ordered_vertices.reserve(number_of_people);
        bool there_is_no_cycles = true;
        for (short vertex_number = 0; vertex_number < number_of_people;
             ++vertex_number) {
            if (colors[vertex_number] == 'w') {
                DFS(vertex_number, vertices, colors,
                    topological_ordered_vertices, there_is_no_cycles);
            }
        }
        if (there_is_no_cycles) {
            // std::cout << number_of_people;
            // return 0;
            continue;
        }
        for (char& color : colors) {
            color = 'w';
        }
        std::vector<short> vertex_component(number_of_people, 0);
        short component_number = 0;
        for (short vertex_position = number_of_people - 1; vertex_position > -1;
             --vertex_position) {
            if (colors[topological_ordered_vertices[vertex_position]] == 'w') {
                BDFS(topological_ordered_vertices[vertex_position], vertices,
                     colors, component_number, vertex_component);
                component_number++;
            }
        }
        std::vector<short> component_size(component_number, 0);
        for (short id : vertex_component) {
            component_size[id]++;
        }
        std::vector<bool> component_has_incoming_edges(component_number, false);
        for (short vertex_a = 0; vertex_a < number_of_people; vertex_a++) {
            for (short vertex_b : vertices[vertex_a].outcoming) {
                if (vertex_component[vertex_a] != vertex_component[vertex_b]) {
                    component_has_incoming_edges[vertex_component[vertex_b]] =
                        true;
                }
            }
        }
        short min_component_size = number_of_people;
        for (short component_id = 0; component_id < component_number;
             component_id++) {
            if (!component_has_incoming_edges[component_id] &&
                component_size[component_id] < min_component_size) {
                min_component_size = component_size[component_id];
            }
        }
        // std::cout << number_of_people - min_component_size + 1;
        // return 0;
    }
    std::cerr << "ОШИБОК НЕ НАЙДЕНО\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    StressTest();

    return 0;
}