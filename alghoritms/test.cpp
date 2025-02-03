#include <algorithm>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <queue>
#include <random>
#include <vector>

std::vector<std::vector<int>> wck_matrix_global = {};
int pack_size;
int k_groups;

struct QueueWithMax {
    std::queue<int64_t> cur_queque = {};
    std::deque<int64_t> cur_dq = {};
    int counter = 0;
    int cost;
    QueueWithMax(int cur_cost) { cost = cur_cost; }
    void Push(int64_t elem) {
        cur_queque.push(elem - cost * counter);
        while (!cur_dq.empty() && elem - cost * counter > cur_dq.back()) {
            cur_dq.pop_back();
        }
        cur_dq.push_back(elem - cost * counter);
        ++counter;
    }
    void Pop() {
        if (cur_dq.front() == cur_queque.front()) {
            cur_dq.pop_front();
        }
        cur_queque.pop();
    }
    int64_t GetMax() { return cur_dq.front() + cost * (counter - 1); }
};

void FillRow(std::vector<int64_t>& row, std::vector<int64_t>& pre_row,
             int cur_weight, int cur_cost, int cur_k) {
    int index_to_fill = 0;
    int cur_index = 0;
    QueueWithMax que = QueueWithMax(cur_cost);
    while (index_to_fill < cur_weight) {
        cur_index = index_to_fill;
        que = QueueWithMax(cur_cost);
        while (cur_index < pack_size + 1) {
            que.Push(pre_row[cur_index]);
            if (que.cur_queque.size() > static_cast<size_t>(cur_k + 1)) {
                que.Pop();
            }
            row[cur_index] = que.GetMax();
            cur_index += cur_weight;
        }
        ++index_to_fill;
    }
    for (int index_in_row = 1; index_in_row <= pack_size; ++index_in_row) {
        if (row[index_in_row] < row[index_in_row - 1]) {
            row[index_in_row] = row[index_in_row - 1];
        }
    }
}

int64_t FillDP() {
    std::vector<int64_t> row;
    std::vector<int64_t> pre_row(pack_size + 1);
    std::vector<int64_t> zero_vec(pack_size + 1);
    int cur_weight;
    int cur_cost;
    int cur_k;
    for (int i_row = 0; i_row < k_groups; ++i_row) {
        row = zero_vec;
        cur_weight = wck_matrix_global[i_row][0];
        cur_cost = wck_matrix_global[i_row][1];
        cur_k = wck_matrix_global[i_row][2];
        if (cur_weight <= pack_size) {
            FillRow(row, pre_row, cur_weight, cur_cost, cur_k);
            pre_row = row;
        }
    }
    return pre_row.back();
}

int64_t RightSol() {
    std::vector<int64_t> pre_row(pack_size + 1);
    std::vector<int64_t> zero_vec(pack_size + 1);
    std::vector<int64_t> row;
    for (int counter = 0; counter < k_groups; ++counter) {
        int ww = wck_matrix_global[counter][0];
        int cc = wck_matrix_global[counter][1];
        int kk = wck_matrix_global[counter][2];
        for (int64_t i = 0; i < kk; ++i) {
            row = {0};
            for (int64_t j = 1; j <= pack_size; ++j){
                if (ww <= j) {
                    row.push_back(std::max({row[j - 1], pre_row[j - ww] + cc, pre_row[j]}));
                } else {
                    row.push_back(std::max(row[j - 1], pre_row[j]));
                }
            }
            pre_row = row;
        }
    }
    return pre_row.back();
}

int64_t knapSack(int W, std::vector<int64_t> wt, std::vector<int64_t> val, int n)
{
    // Making and initializing dp array
    std::vector<int64_t> dp(W + 1);

    for (int i = 1; i < n + 1; i++) {
        for (int w = W; w >= 0; w--) {

            if (wt[i - 1] <= w)
                
                // Finding the maximum value
                dp[w] = std::max(dp[w],
                            dp[w - wt[i - 1]] + val[i - 1]);
        }
    }
    // Returning the maximum value of knapsack
    return dp[W];
}



void StressTest() {
    std::mt19937 generator(1337);
    std::uniform_int_distribution<int> pack_size_random(1, 100);
    std::uniform_int_distribution<int> k_groups_random(1, 3);
    for (int i = 0; i < 1000; ++i) {
        wck_matrix_global = {};
        pack_size = pack_size_random(generator);
        k_groups = k_groups_random(generator);
        std::uniform_int_distribution<int> w_random(1, 20);
        std::uniform_int_distribution<int> c_random(1, 100);
        std::uniform_int_distribution<int> k_random(1, 100);
        for (int counter = 0; counter != k_groups; ++counter) {
            wck_matrix_global.push_back({});
            int ww = w_random(generator);
            int cc = c_random(generator);
            int kk = k_random(generator);
            wck_matrix_global.back().push_back(ww);
            wck_matrix_global.back().push_back(cc);
            wck_matrix_global.back().push_back(kk);
        }
        std::vector<std::vector<int>> wck = wck_matrix_global;
        int pack_size_loc = pack_size;
        std::vector<int64_t> wt, val;
        int n = 0;
        for (auto v : wck) {
            for (int j = 0; j < v[2]; ++j) {
                wt.push_back(v[0]);
                val.push_back(v[1]);
                ++n;
            }
        }
        int64_t ans = knapSack(pack_size_loc, wt, val, n);
        int64_t my_ans = FillDP();
        if (ans != my_ans) {
            std::cout << "ALARM!" << "\n";  
            std::cout << k_groups << " " << pack_size << "\n";
            for (auto str : wck_matrix_global) {
                for (auto v : str) {
                    std::cout << v << " ";
                }
                std::cout << "\n";
            }
            std::cout << "My: " << my_ans << " " << "Right: " << ans << "\n";
            break;
        }
        if (i % 100 == 0 ) {
            std::cout << i << "\n";
        }
    }
}


int main() {
    // std::cin >> k_groups;
    // std::cin >> pack_size;
    // int ww;
    // int cc;
    // int kk;
    // for (int counter = 0; counter != k_groups; ++counter) {
    //     wck_matrix_global.push_back({});
    //     std::cin >> ww >> cc >> kk;
    //     wck_matrix_global.back().push_back(ww);
    //     wck_matrix_global.back().push_back(cc);
    //     wck_matrix_global.back().push_back(kk);
    // }
    // FillDP();
    // std::cout << FillDP() << " " << RightSol();
    StressTest();
}
