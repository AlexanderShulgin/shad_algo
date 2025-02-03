#include <iostream>
#include <vector>

const int kMaxCost = 2'000'000'000;
struct Edge {
    Edge(int end1, int cost1) : end(std::move(end1)), cost(std::move(cost1)){};
    int end;
    int cost;
};

struct AllInfo {
    std::vector<char> colors;
    std::vector<int> lambdas;
    std::vector<int> enter_times;
    int minimum_cost;
};
void DFS(int vertex_id, std::vector<std::vector<Edge>>& edges, AllInfo& info,
         int& time, int came_from) {
    info.enter_times[vertex_id] = time++;
    info.colors[vertex_id] = 'g';
    info.lambdas[vertex_id] = time - 1;
    for (Edge& edge : edges[vertex_id]) {
        if (edge.end == came_from) {
            continue;
        }
        if (info.colors[edge.end] == 'g') {
            info.lambdas[vertex_id] =
                std::min(info.lambdas[vertex_id], info.enter_times[edge.end]);
        }
        if (info.colors[edge.end] == 'w') {
            DFS(edge.end, edges, info, time, vertex_id);
            info.lambdas[vertex_id] =
                std::min(info.lambdas[vertex_id], info.lambdas[edge.end]);
            if (info.enter_times[vertex_id] < info.lambdas[edge.end]) {
                info.minimum_cost = std::min(info.minimum_cost, edge.cost);
            }
        }
    }
    info.colors[vertex_id] = 'b';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_towns;
    int number_of_roads;
    std::cin >> number_of_towns >> number_of_roads;

    std::vector<std::vector<Edge>> edges(number_of_towns);
    for (int edge_id = 0; edge_id < number_of_roads; ++edge_id) {
        int begin;
        int end;
        int cost;
        std::cin >> begin >> end >> cost;
        if (begin == end) {
            continue;
        }
        begin--;
        end--;
        edges[begin].emplace_back(end, cost);
        edges[end].emplace_back(begin, cost);
    }
    int time = 0;
    AllInfo info{std::vector<char>(number_of_towns, 'w'),
                 std::vector<int>(number_of_towns),
                 std::vector<int>(number_of_towns), kMaxCost};
    DFS(0, edges, info, time, -1);
    if (info.minimum_cost == kMaxCost) {
        std::cout << -1;
    } else {
        std::cout << info.minimum_cost;
    }
    return 0;
}