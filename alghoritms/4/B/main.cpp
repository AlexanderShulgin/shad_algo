#include <algorithm>
#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

const int kMax = 20000000;
int GetRandomPriority(std::mt19937* gen) {
    std::uniform_int_distribution<int> dist(-kMax, kMax);
    return dist(*gen);
}

struct Interval {
    Interval(int aa, int bb, int yy, bool begbeg)
        : a(aa), b(bb), y(yy), begin(begbeg){};
    int a;
    int b;
    int y;
    bool begin;
};

struct Node {
    Node(int aa, int bb, int pp)
        : a_key(std::move(aa)), b_key(std::move(bb)), priority(std::move(pp)){};
    int a_key;
    int b_key;
    int priority;
    Node* left_son = nullptr;
    Node* right_son = nullptr;
    ~Node() {
        delete left_son;
        delete right_son;
    };
};

struct SplitAns {
    SplitAns(Node* ga, Node* ve, Node* de)
        : gamma(std::move(ga)), vertex(std::move(ve)), delta(std::move(de)){};
    Node* gamma;
    Node* vertex;
    Node* delta;
};

Node* Merge(Node* tree1, Node* tree2) {
    if (tree1 == nullptr) {
        return tree2;
    }
    if (tree2 == nullptr) {
        return tree1;
    }
    if (tree1->priority <= tree2->priority) {
        tree1->right_son = Merge(tree1->right_son, tree2);
        return tree1;
    }
    tree2->left_son = Merge(tree1, tree2->left_son);
    return tree2;
}

SplitAns Split(Node* tree, int lambda_a, int lambda_b) {
    if (tree == nullptr) {
        return SplitAns(nullptr, nullptr, nullptr);
    }
    if (tree->a_key == lambda_a && tree->b_key == lambda_b) {
        Node* alpha = tree->left_son;
        Node* beta = tree->right_son;
        tree->left_son = nullptr;
        tree->right_son = nullptr;
        return SplitAns(alpha, tree, beta);
    }
    if (tree->a_key < lambda_a) {
        SplitAns ans = Split(tree->right_son, lambda_a, lambda_b);
        tree->right_son = ans.gamma;
        return SplitAns(tree, ans.vertex, ans.delta);
    }
    SplitAns ans = Split(tree->left_son, lambda_a, lambda_b);
    tree->left_son = ans.delta;
    return SplitAns(ans.gamma, ans.vertex, tree);
}

Node* DeleteNode(Node* tree, int lambda_a, int lambda_b, int& count) {
    SplitAns ans = Split(tree, lambda_a, lambda_b);
    if (ans.vertex != nullptr) {
        count += 1;
        delete ans.vertex;
    }
    return Merge(ans.gamma, ans.delta);
}

Node* UpdateNode(Node* tree, int lambda_a, int lambda_b, int priority) {
    if (tree == nullptr) {
        return new Node(lambda_a, lambda_b, priority);
    }
    if (lambda_b < tree->a_key) {
        if (tree->left_son == nullptr) {
            tree->left_son = new Node(lambda_a, lambda_b, priority);
            return tree;
        }
        tree->left_son =
            UpdateNode(tree->left_son, lambda_a, lambda_b, priority);
        return tree;
    }
    if (tree->b_key < lambda_a) {
        if (tree->right_son == nullptr) {
            tree->right_son = new Node(lambda_a, lambda_b, priority);
            return tree;
        }
        tree->right_son =
            UpdateNode(tree->right_son, lambda_a, lambda_b, priority);
        return tree;
    }
    return tree;
}

int CountForeignRectangulars(std::vector<Interval>& events) {
    std::mt19937 generator(72874);  // NOLINT
    int counter = 0;
    Node* tree = nullptr;
    for (size_t index = 0; index < events.size(); index++) {
        Interval event = events[index];
        if (!event.begin) {
            tree = DeleteNode(tree, event.a, event.b, counter);
        } else {
            tree = UpdateNode(tree, event.a, event.b,
                              GetRandomPriority(&generator));
        }
    }
    delete tree;
    return counter;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_rectangulars;
    std::cin >> number_of_rectangulars;
    std::vector<Interval> intervals;
    intervals.reserve(number_of_rectangulars * 2);
    for (int index = 0; index < number_of_rectangulars; index++) {
        int x1;
        int y1;
        int x2;
        int y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            std::swap(x1, x2);
        }
        if (y1 > y2) {
            std::swap(y1, y2);
        }
        intervals.emplace_back(x1, x2, y1, true);
        intervals.emplace_back(x1, x2, y2, false);
    }
    std::sort(intervals.begin(), intervals.end(),
              [](Interval& first, Interval& second) {
                  if (first.y == second.y) {
                      return first.a < second.a;
                  }
                  return first.y < second.y;
              });
    std::cout << CountForeignRectangulars(intervals);
    return 0;
}