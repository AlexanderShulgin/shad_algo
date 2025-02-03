#include <algorithm>
#include <iostream>
#include <vector>
struct Edge {
    Edge(short aga, short agb, int co)
        : vertex_a(aga), vertex_b(agb), cost(co){};
    short vertex_a;
    short vertex_b;
    int cost;
};

struct Node {
    short parent_id = -1;
    short rank = 1;
};
short FindRoot(std::vector<Node>& dsu, short vertex_id) {
    if (dsu[vertex_id].parent_id == -1) {
        return vertex_id;
    }
    short root_id = vertex_id;
    while (dsu[root_id].parent_id != -1) {
        root_id = dsu[root_id].parent_id;
    }
    while (dsu[vertex_id].parent_id != -1) {
        short parent_id = dsu[vertex_id].parent_id;
        dsu[vertex_id].parent_id = root_id;
        vertex_id = parent_id;
    }
    return root_id;
}

void AddEdgeToDSU(std::vector<Node>& dsu, short& disjoint_set_amount,
                  short vertex_a, short vertex_b) {
    short a_root = FindRoot(dsu, vertex_a);
    short b_root = FindRoot(dsu, vertex_b);
    if (a_root == b_root) {
        return;
    }
    disjoint_set_amount--;
    if (dsu[a_root].rank < dsu[b_root].rank) {
        dsu[a_root].parent_id = b_root;
    } else if (dsu[a_root].rank < dsu[b_root].rank) {
        dsu[b_root].parent_id = a_root;
    } else {
        dsu[a_root].parent_id = b_root;
        dsu[b_root].rank += 1;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_vertices;
    int number_of_edges;
    std::cin >> number_of_vertices >> number_of_edges;

    std::vector<Edge> edges;
    edges.reserve(number_of_edges);
    for (int edge_index = 0; edge_index < number_of_edges; edge_index++) {
        short v_a;
        short v_b;
        int expensive;
        std::cin >> v_a >> v_b >> expensive;
        if (v_a == v_b) {
            continue;
        }
        edges.emplace_back(v_a, v_b, expensive);
    }

    std::sort(edges.begin(), edges.end(), [](Edge& first, Edge& second) {
        return first.cost < second.cost;
    });

    std::vector<Node> dsu(number_of_vertices + 1);
    short disjoint_set_amount = number_of_vertices;
    for (Edge& edge : edges) {
        AddEdgeToDSU(dsu, disjoint_set_amount, edge.vertex_a, edge.vertex_b);
        if (disjoint_set_amount == 1) {
            std::cout << edge.cost;
            return 0;
        }
    }
    return 0;
}
