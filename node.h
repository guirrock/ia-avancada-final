#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>

class Node {
public:
    std::vector<int> initialVector;
    Node* parent;
    int insertionOrder;
    std::vector<Node*> children;

    Node(std::vector<int> _initialVector, Node* _parent, int _insertionOrder);
    
	Node(std::vector<int> _initialVector, Node* _parent);

    int findZero();
    void printPuzzle();
    void moveUp(int order);
    void moveDown(int order);
    void moveLeft(int order);
    void moveRight(int order);

};

#endif // NODE_H
