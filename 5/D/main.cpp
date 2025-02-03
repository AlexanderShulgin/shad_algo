#include <iostream>
#include <queue>
#include <vector>
struct Edge {
    short vertex_id = 0;
    char weight;
};

void UpdateQwewe(std::queue<short>& qwewe,
                 std::vector<std::vector<Edge>>& edges,
                 std::vector<char>& visited, short vertex_id) {
    qwewe.push(vertex_id);
    visited[vertex_id] = 'b';
    for (Edge& outcoming_edge : edges[vertex_id]) {
        if (outcoming_edge.weight == '0' &&
            visited[outcoming_edge.vertex_id] == 'w') {
            UpdateQwewe(qwewe, edges, visited, outcoming_edge.vertex_id);
        }
    }
}

void GiveAnswer(std::vector<std::vector<Edge>>& edges, short added_vertex_id,
                short from, short to) {
    std::vector<char> visited(added_vertex_id, 'w');

    std::queue<short> qwewe;
    UpdateQwewe(qwewe, edges, visited, from);
    short level = 0;

    while (!qwewe.empty()) {
        int qwewe_size = qwewe.size();
        while (qwewe_size > 0) {
            short vertex = qwewe.front();
            if (vertex == to) {
                std::cout << level << "\n";
                return;
            }

            for (Edge& outcoming_edge : edges[vertex]) {
                short future_vertex = outcoming_edge.vertex_id;
                if (visited[future_vertex] == 'w') {
                    UpdateQwewe(qwewe, edges, visited, future_vertex);
                }
            }
            qwewe.pop();
            qwewe_size--;
        }
        level++;
    }
    std::cout << -1 << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_vertices;
    short number_of_edges;
    std::cin >> number_of_vertices >> number_of_edges;
    short added_vertex_id = number_of_vertices;
    std::vector<std::vector<Edge>> edges(number_of_vertices + number_of_edges);
    for (short edge_index = 0; edge_index < number_of_edges; edge_index++) {
        short begin;
        short end;
        short weight;
        std::cin >> begin >> end >> weight;
        if (begin == end) {
            continue;
        }
        if (weight == 0) {
            edges[begin - 1].push_back(Edge{static_cast<short>(end - 1), '0'});
        } else if (weight == 1) {
            edges[begin - 1].push_back(Edge{static_cast<short>(end - 1), '1'});
        } else {
            edges[begin - 1].push_back(Edge{added_vertex_id, '1'});
            edges[added_vertex_id].push_back(
                Edge{static_cast<short>(end - 1), '1'});
            added_vertex_id++;
        }
    }

    short number_of_queries;
    std::cin >> number_of_queries;
    short from;
    short to;
    for (short query_number = 0; query_number < number_of_queries;
         query_number++) {
        std::cin >> from >> to;
        GiveAnswer(edges, added_vertex_id, from - 1, to - 1);
    }
}