#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cstring>

const int SIZE = 8;

/*
Граф:
           А
        /     \
       B       C
     /   \      \
    D     E      F
    \      \   /
     G       H

*/
// матрица смежности
                              // A  B  C  D  E  F  G  H
const int matrix[SIZE][SIZE] = {{0, 1, 1, 0, 0, 0, 0, 0},     // A
                                {1, 0, 0, 1, 1, 0, 0, 0},     // B
                                {1, 0, 0, 0, 0, 1, 0, 0},     // C
                                {0, 1, 0, 0, 0, 0, 1, 0},     // D
                                {0, 1, 0, 0, 0, 0, 0, 1},     // E
                                {0, 0, 1, 0, 0, 0, 0, 1},     // F
                                {0, 0, 0, 1, 0, 0, 0, 0},     // G
                                {0, 0, 0, 0, 1, 1, 0, 0}};    // H

const char vertexName[SIZE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
static std::set<char> visited;

// поиск в глубину
void depthFirstSearch(int vertex = 0)
{
    visited.emplace(vertexName[vertex]);
    std::cout << "Visited: " << vertexName[vertex] << std::endl;
    for (int i = vertex; i < SIZE; ++i)
        if (matrix[vertex][i] == 1 && !static_cast<bool>(visited.count(vertexName[i])))
            depthFirstSearch(i);
}

// поиск в ширину
void breadthFirstSearch(std::vector<int> arrayVertex, int depth = 0)
{
    std::cout << "Visited on depth " << depth << ": ";
    for (const auto &el : arrayVertex)
        std::cout << vertexName[el] << " ";
    std::cout << std::endl;

    std::vector<int> newArrayVertex;
    for (const auto &el : arrayVertex) {
        for (int i = el; i < SIZE; ++i) {
            if (matrix[el][i] == 1 && !static_cast<bool>(visited.count(vertexName[i]))) {
                newArrayVertex.push_back(i);
                visited.emplace(i + 65);
            }
        }
    }
    if (!newArrayVertex.empty())
        breadthFirstSearch(newArrayVertex, ++depth);

}
// задача
void computeTask(int numberUnit) {

    std::map<std::string, int> firstSide = {{"Soldier", numberUnit},
                                            {"Boy", 2}};
    std::map<std::string, int> secondSide = {{"Soldier", 0},
                                             {"Boy", 0}};
    bool boatOnFirstSide = true;

    while (static_cast<bool>(firstSide["Soldier"])) {
        if (firstSide["Boy"] == 2) {
            firstSide["Boy"] -= 2;
            secondSide["Boy"] += 2;
            boatOnFirstSide = false;
            std::cout << "2 boy -> second side" << std::endl;
        } else if (secondSide["Boy"] >= 1 && !boatOnFirstSide) {
            ++firstSide["Boy"];
            --secondSide["Boy"];
            boatOnFirstSide = true;
            std::cout << "1 boy -> first side" << std::endl;
        } else if (firstSide["Boy"] == 1) {
            --firstSide["Soldier"];
            ++secondSide["Soldier"];
            boatOnFirstSide = false;
            std::cout << "1 Soldier -> second side" << std::endl;
        }
    }
}

int main()
{
    depthFirstSearch();

    visited.clear();
    std::cout << std::endl;

    std::vector<int> arrayVertex = {0};
    breadthFirstSearch(arrayVertex);

    int numberUnit = 0/*, firstSide = 0, secondSide = 0*/;
    std::cout << "Number of military unit \n>";
    std::cin >> numberUnit;
//    std::cout << "The number on the home shore \n>";
//    std::cin >> firstSide;
//    std::cout << "The number at the end of the beach \n>";
//    std::cin >> secondSide;

    computeTask(numberUnit);

    system("pause");
    return 0;
}
