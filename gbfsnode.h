#ifndef GBFSNODE_H
#define GBFSNODE_H

#include "node.h"

class GBFSNode {
public:
    Node* node;
    int gCost;
    int hCost;

    GBFSNode(Node* _node, int _gCost, int _hCost);
};

struct GBFSComparator {
    bool operator()(const GBFSNode& a, const GBFSNode& b) const;
};

#endif // GBFSNODE_H
