#include <iostream>
#include <cstring>
#include "balancetree.h"

using namespace std;

int main()
{
    BalanceTree<char> tree;
    string str = "hello_world";

    for (auto &el : str)
        tree.insert(el);

    tree.print();
    cout << "-------------\n"
            "Add 'k'\n"
            "-------------\n";
    tree.insert('k');
    tree.print();

    cout << "-------------\n"
            "Remove 'o'\n"
            "-------------\n";
    tree.remove('o');
    tree.print();

    return 0;
}
