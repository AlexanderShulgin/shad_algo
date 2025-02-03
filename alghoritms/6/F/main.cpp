#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
struct Edge {
    Edge(short aga, short agb, int x_dif, int y_dif)
        : agent_a(aga),
          agent_b(agb),
          length_squared(static_cast<long>(x_dif) * x_dif +
                         static_cast<long>(y_dif) * y_dif){};
    short agent_a;
    short agent_b;
    long int length_squared;
};

struct Node {
    short parent_id = -1;
    short rank = 1;
};
short FindRoot(std::vector<Node>& dsu, short agent_id) {
    if (dsu[agent_id].parent_id == -1) {
        return agent_id;
    }
    short root_id = agent_id;
    while (dsu[root_id].parent_id != -1) {
        root_id = dsu[root_id].parent_id;
    }
    while (dsu[agent_id].parent_id != -1) {
        short parent_id = dsu[agent_id].parent_id;
        dsu[agent_id].parent_id = root_id;
        agent_id = parent_id;
    }
    return root_id;
}

void AddEdgeToDSU(std::vector<Node>& dsu, short& disjoint_set_amount,
                  short agent_a, short agent_b) {
    short a_root = FindRoot(dsu, agent_a);
    short b_root = FindRoot(dsu, agent_b);
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
    const int kPr = 10;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short number_of_agents;
    std::cin >> number_of_agents;
    if (number_of_agents == 1) {
        std::cout << std::fixed;
        std::cout << std::setprecision(kPr) << static_cast<double>(0);
        return 0;
    }
    std::vector<std::pair<int, int>> agents;
    agents.reserve(number_of_agents);
    for (short agent_id = 0; agent_id < number_of_agents; agent_id++) {
        int x_coordinate;
        int y_coordinate;
        std::cin >> x_coordinate >> y_coordinate;
        agents.emplace_back(x_coordinate, y_coordinate);
    }

    std::vector<Edge> edges;
    edges.reserve(static_cast<int>(number_of_agents - 1) * number_of_agents /
                  2);
    for (short agent_a_id = 0; agent_a_id < number_of_agents - 1;
         agent_a_id++) {
        for (short agent_b_id = agent_a_id + 1; agent_b_id < number_of_agents;
             agent_b_id++) {
            edges.emplace_back(
                agent_a_id, agent_b_id,
                agents[agent_a_id].first - agents[agent_b_id].first,
                agents[agent_a_id].second - agents[agent_b_id].second);
        }
    }
    std::sort(edges.begin(), edges.end(), [](Edge& first, Edge& second) {
        return first.length_squared < second.length_squared;
    });

    std::vector<Node> dsu(number_of_agents);
    short disjoint_set_amount = number_of_agents;
    for (Edge& edge : edges) {
        AddEdgeToDSU(dsu, disjoint_set_amount, edge.agent_a, edge.agent_b);
        if (disjoint_set_amount == 1) {
            std::cout << std::fixed;
            std::cout << std::setprecision(kPr)
                      << std::sqrt(static_cast<double>(edge.length_squared));
            return 0;
        }
    }
    return 0;
}
