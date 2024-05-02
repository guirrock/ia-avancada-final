#include "bfsnode.h"

BFSNode::BFSNode(Node* initialNode) {
    openList.push(initialNode);
    visited[initialNode->initialVector] = true;
}

void BFSNode::addNode(Node* node) {
    openList.push(node);
}

Node* BFSNode::getNextNode() {
    if (openList.empty()) {
        return nullptr;
    }
    Node* nextNode = openList.front();
    openList.pop();
    return nextNode;
}

bool BFSNode::isVisited(const std::vector<int>& state) {
    return visited.count(state) > 0;
}

void BFSNode::setVisited(const std::vector<int>& state) {
    visited[state] = true;
}
