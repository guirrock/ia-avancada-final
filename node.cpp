#include "node.h"
#include <algorithm>

Node::Node(std::vector<int> _initialVector, Node* _parent, int _insertionOrder)
    : initialVector(_initialVector), parent(_parent), insertionOrder(_insertionOrder) {}
    
//Node::Node(std::vector<int> _initialVector, Node* _parent)
  //  : initialVector(_initialVector), parent(_parent) {}    

int Node::findZero() {
    auto it = std::find(initialVector.begin(), initialVector.end(), 0);
    return static_cast<int>(std::distance(initialVector.begin(), it));
}

void Node::printPuzzle() {
    int count = 0;
    for (auto i : initialVector) {
        if (count % 3 == 0) {
            std::cout << "\n";
        }
        std::cout << i << ' ';
        count++;
    }
}

void Node::moveUp(int order) {
    int zPos = findZero();
    if (zPos >= 3) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos - 3]);
        Node* child = new Node(temp, this, order);
        children.push_back(child);
    }
}

void Node::moveDown(int order) {
    int zPos = findZero();
    if (zPos < 6) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos + 3]);
        Node* child = new Node(temp, this, order);
        children.push_back(child);
    }
}

void Node::moveLeft(int order) {
    int zPos = findZero();
    if (zPos % 3 > 0) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos - 1]);
        Node* child = new Node(temp, this, order);
        children.push_back(child);
    }
}

void Node::moveRight(int order) {
    int zPos = findZero();
    if (zPos % 3 < 2) {
        std::vector<int> temp = initialVector;
        std::swap(temp[zPos], temp[zPos + 1]);
        Node* child = new Node(temp, this, order);
        children.push_back(child);
    }
}
