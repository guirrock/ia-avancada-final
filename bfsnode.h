#ifndef BFSNODE_H
#define BFSNODE_H

#include "node.h"
#include <queue>
#include <map>
#include <vector>

class BFSNode {
public:
    std::queue<Node*> openList; // Fila para os nós abertos (em busca)
    std::map<std::vector<int>, bool> visited; // Conjunto de estados já visitados

    BFSNode(Node* initialNode);

    void addNode(Node* node);
    Node* getNextNode();
    bool isVisited(const std::vector<int>& state);
    void setVisited(const std::vector<int>& state);
};

#endif // BFSNODE_H
