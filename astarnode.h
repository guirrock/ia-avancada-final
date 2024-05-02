#ifndef ASTARNODE_H
#define ASTARNODE_H

#include "node.h"

class AstarNode {
public:
    Node* node;
    int gCost;
    int hCost;
    int fCost;
    std::vector<Node*> children;

    AstarNode(Node* _node, int _gCost, int _hCost, int _fCost);
};

struct AstarComparator {
    bool operator()(const AstarNode& a, const AstarNode& b) const;
};

#endif // ASTARNODE_H
