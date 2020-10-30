#include <iostream>
#include <cstring>
#include "hashtable.h"

using namespace std;

int main()
{
    HashTable<int> table;

    for (char i = 'a'; i < 'z'; ++i)
        ++table[i];

    table.print();

    cout << "-------------\n"
            "Add '#' = 22 to hash-table\n"
            "-------------\n";
    table['#'] = 22;    // or table.insert('#', 22)
    table.print();

    cout << "-------------\n"
            "Remove 'k'\n"
            "-------------\n";
    table.remove('k');
    table.print();

    cout << "-------------\n"
            "Number of 'd'\n"
            "-------------\n";
    cout << "d: "<< table['d'] << endl;

    system("pause");
    return 0;
}
