#include <iostream>
#include <cstring>
#include "binarytree.h"

using namespace std;

int main()
{
    BinaryTree<char> tree;
    string str = "hello_world";

    for (auto &el : str)
        tree.insert(el);

    tree.print();
    cout << "-------------\n"
            "Add '#'\n"
            "-------------\n";
    tree.insert('#');
    tree.print();

    cout << "-------------\n"
            "Remove 'l'\n"
            "-------------\n";
    tree.remove('l');
    tree.print();

    cout << "-------------\n"
            "Next after 'e'\n"
            "-------------\n";
    cout << "Next: " << tree.next('e') << endl;

    system("pause");
    return 0;
}
