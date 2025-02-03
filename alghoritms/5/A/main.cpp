#include <iostream>
#include <vector>
struct VertexEdges {
    std::vector<int> incoming;
    std::vector<int> outcoming;
};

std::vector<VertexEdges> ReadInput(int& number_of_people) {
    int number_of_games;
    std::cin >> number_of_people >> number_of_games;

    std::vector<VertexEdges> vertices(number_of_people);
    for (int _ = 0; _ < number_of_games; _++) {
        int first_player;
        int second_player;
        int winner;
        std::cin >> first_player >> second_player >> winner;
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
    return vertices;
}

void DFS(int vertex_number, std::vector<VertexEdges>& vertices,
         std::vector<char>& colors,
         std::vector<int>& topological_ordered_vertices,
         bool& there_is_no_cycles) {
    colors[vertex_number] = 'g';
    for (int future_vertex : vertices[vertex_number].outcoming) {
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

void BDFS(int vertex_number, std::vector<VertexEdges>& vertices,
          std::vector<char>& colors, int& component_number,
          std::vector<int>& vertex_component) {
    colors[vertex_number] = 'b';
    vertex_component[vertex_number] = component_number;
    for (int future_vertex : vertices[vertex_number].incoming) {
        if (colors[future_vertex] == 'w') {
            BDFS(future_vertex, vertices, colors, component_number,
                 vertex_component);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int number_of_people;
    std::vector<VertexEdges> vertices = ReadInput(number_of_people);
    if (number_of_people == 1) {
        std::cout << 1;
        return 0;
    }
    std::vector<char> colors(number_of_people, 'w');
    std::vector<int> topological_ordered_vertices;
    topological_ordered_vertices.reserve(number_of_people);
    bool there_is_no_cycles = true;
    for (int vertex_number = 0; vertex_number < number_of_people;
         ++vertex_number) {
        if (colors[vertex_number] == 'w') {
            DFS(vertex_number, vertices, colors, topological_ordered_vertices,
                there_is_no_cycles);
        }
    }
    if (there_is_no_cycles) {
        std::cout << number_of_people;
        return 0;
    }
    for (char& color : colors) {
        color = 'w';
    }
    std::vector<int> vertex_component(number_of_people, 0);
    int component_number = 0;
    for (int vertex_position = number_of_people - 1; vertex_position > -1;
         --vertex_position) {
        if (colors[topological_ordered_vertices[vertex_position]] == 'w') {
            BDFS(topological_ordered_vertices[vertex_position], vertices,
                 colors, component_number, vertex_component);
            component_number++;
        }
    }
    std::vector<int> component_size(component_number, 0);
    for (int id : vertex_component) {
        component_size[id]++;
    }
    std::vector<bool> component_has_incoming_edges(component_number, false);
    for (int vertex_a = 0; vertex_a < number_of_people; vertex_a++) {
        for (int vertex_b : vertices[vertex_a].outcoming) {
            if (vertex_component[vertex_a] != vertex_component[vertex_b]) {
                component_has_incoming_edges[vertex_component[vertex_b]] = true;
            }
        }
    }
    int min_component_size = number_of_people;
    for (int component_id = 0; component_id < component_number;
         component_id++) {
        if (!component_has_incoming_edges[component_id] &&
            component_size[component_id] < min_component_size) {
            min_component_size = component_size[component_id];
        }
    }
    std::cout << number_of_people - min_component_size + 1;
    return 0;
}