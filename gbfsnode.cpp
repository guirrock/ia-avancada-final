#include "gbfsnode.h"

GBFSNode::GBFSNode(Node* _node, int _gCost, int _hCost)
    : node(_node), gCost(_gCost), hCost(_hCost) {}

bool GBFSComparator::operator()(const GBFSNode& a, const GBFSNode& b) const {
    if (a.hCost == b.hCost) {
        if (a.gCost == b.gCost) {
            return a.node->insertionOrder < b.node->insertionOrder; // LIFO para empates
        }
        return a.gCost < b.gCost; // Maior gCost
    }
    return a.hCost > b.hCost; // Prioridade para menor hCost
}

