#include "astarnode.h"

AstarNode::AstarNode(Node* _node, int _gCost, int _hCost, int _fCost)
    : node(_node), gCost(_gCost), hCost(_hCost), fCost(_fCost) {}

bool AstarComparator::operator()(const AstarNode& a, const AstarNode& b) const {
    if (a.fCost == b.fCost) {
        if (a.hCost == b.hCost) {
            return a.node->insertionOrder < b.node->insertionOrder;
        } else {
            return a.hCost > b.hCost;
        }
    }
    return a.fCost > b.fCost;
}
