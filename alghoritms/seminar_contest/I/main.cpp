#include <error.h>

#include <iostream>
#include <vector>
struct Node {
    int child_id = -1;
    int subtree_size = 0;
};

int SetTree(std::vector<Node>& tree, int from, int to, int index) {
    if (from == to) {
        tree[index] = {from, 1};
        return 1;
    }
    if (from + 1 == to) {
        tree[index] = {to, 1 + SetTree(tree, from, to - 1, 2 * index)};
        return 2;
    }
    int pivot = (to + from + 1) / 2;
    tree[index] = {pivot, 1 + SetTree(tree, from, pivot - 1, 2 * index) +
                              SetTree(tree, pivot + 1, to, 1 + 2 * index)};
    return tree[index].subtree_size;
}

void PrintTree(std::vector<Node>& tree, int index = 1) {
    if (tree[index].subtree_size == 1 && tree[index].child_id != -1) {
        std::cout << "id" << tree[index].child_id << "size"
                  << tree[index].subtree_size;
        return;
    }
    if (tree[index].subtree_size == 0) {
        return;
    }
    std::cout << "(";
    PrintTree(tree, 2 * index);
    std::cout << ")"
              << "id" << tree[index].child_id << "size"
              << tree[index].subtree_size << "(";
    PrintTree(tree, 1 + 2 * index);
    std::cout << ")";
}

int DeleteKth(std::vector<Node>& tree, int kth, int index = 1) {
    if (kth == 1 && tree[index].subtree_size == 1 &&
        tree[index].child_id != -1) {
        int remember_id = tree[index].child_id;
        tree[index].child_id = -1;
        while (index != 0) {
            tree[index].subtree_size--;
            index /= 2;
        }
        return remember_id;
    }
    int left_size = tree[index * 2].subtree_size;
    if (left_size >= kth) {
        return DeleteKth(tree, kth, index * 2);
    }
    if (tree[index].child_id == -1) {
        return DeleteKth(tree, kth - left_size, 1 + 2 * index);
    }
    if (kth == left_size + 1) {
        int remember_id = tree[index].child_id;
        tree[index].child_id = -1;
        while (index != 0) {
            tree[index].subtree_size--;
            index /= 2;
        }
        return remember_id;
    }
    return DeleteKth(tree, kth - left_size - 1, 1 + 2 * index);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_kids;
    int kth;
    std::cin >> number_of_kids >> kth;
    std::vector<Node> tree((number_of_kids + 1) * 2);
    tree[0].child_id = -3;
    tree[0].subtree_size = -3;
    int size = SetTree(tree, 1, number_of_kids, 1);
    if (size == 1) {
        std::cout << 1;
        return 0;
    }
    int position = 1;
    int denominator = number_of_kids;
    for (int round = 1; round <= number_of_kids; round++) {
        position = ((position + kth - 2) % denominator) + 1;
        denominator--;
        std::cout << DeleteKth(tree, position) << " ";
    }
    return 0;
}