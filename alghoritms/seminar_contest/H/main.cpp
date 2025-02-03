#include <iostream>
#include <vector>

struct ZWiseNode{
    short subtree_size;
};
struct YWiseNode{
    std::vector<ZWiseNode> z_wise_tree;
};
struct XWiseNode{
    std::vector<YWiseNode> y_wise_tree;
};



int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    short dummy_number;
    std::cin >> dummy_number;
    short m_value;
    std::cin >> m_value;
    if(dummy_number == 1){
        std::cout << "Идиотский случай, рассмотри отдельно";
    }
    int number = 1;
    while(number < dummy_number){
        number*=2;
    }
    if(number == 1){
        number++;
    }
    std::vector<XWiseNode> x_wise_tree(number-1);
    SetXTree

    while(m_value != 3){
        if(m_value == 1){
            short x_coordinate;
            short y_coordinate;
            short z_coordinate;
            int new_stars;
            std::cin >> x_coordinate >> y_coordinate >> z_coordinate >> new_stars;
            Update();
        } else if(m_value == 2){
            short x1;
            short y1;
            short z1;
            short x2;
            short y2;
            short z2;
            std::cin >> x1>>y1>>z1>>x2>>y2>>z2;
            GetAnswer();
        }
        std::cin >> m_value;
    }
    return 0;
}