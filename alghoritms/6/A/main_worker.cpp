#include <iostream>
#include <sstream>
#include <string_view>
#include <vector>

struct Worker {
    short boss_id = -1;
};
short FindDirector(std::vector<Worker>& dsu, short worker_id) {
    if (dsu[worker_id].boss_id == -1) {
        return worker_id;
    }
    short root_id = worker_id;
    while (dsu[root_id].boss_id != -1) {
        root_id = dsu[root_id].boss_id;
    }
    while (dsu[worker_id].boss_id != -1) {
        short parent_id = dsu[worker_id].boss_id;
        dsu[worker_id].boss_id = root_id;
        worker_id = parent_id;
    }
    return root_id;
}

/*void AddEdgeToDSU(std::vector<Worker>& dsu, short& disjoint_set_amount,
                  short agent_a, short agent_b) {
    short a_root = FindDirector(dsu, agent_a);
    short b_root = FindDirector(dsu, agent_b);
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
}*/
void PrintDsu(std::vector<)

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int number_of_workers;
    int number_of_queries;
    std::string input_line;
    std::getline(std::cin, input_line);
    std::stringstream str1(input_line);
    str1 >> number_of_workers >> number_of_queries;
    
    std::vector<Worker> dsu(number_of_workers+1);


    size_t index;
    for(int query_id = 0; query_id < number_of_queries; query_id++){
        std::string input_line;
        std::getline(std::cin, input_line);
        index = input_line.find(' ');
        if(index == std::string::npos){
            int worker = std::stoi(input_line);
            std::cout<<FindDirector(dsu, worker)<<"\n";
        } else{
            std::stringstream str(input_line);
            int boss;
            int worker;
            str>>boss>>worker;
            if(boss == 3 && worker == 2){
                std::cerr<<"WAIT A MINUTE\n";
            }
            if(dsu[worker].boss_id == -1 && boss!=worker && FindDirector(dsu, boss) != worker){
                std::cout << 1 <<"\n";
                dsu[worker].boss_id = dsu[boss].boss_id;
            } else{
                std::cout << 0 << "\n";
            }
        }
    }
    
    return 0;
}
