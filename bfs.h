#ifndef BFS_H
#define BFS_H

#include "bfsnode.h"
#include "node.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>

class BFS {
public:
    BFS(const std::vector<int>& finalVector);

    std::vector<Node*> solve(const std::vector<int>& initialVector);

    int getNodesCount() const;
    int getSolutionDepth() const;

private:
    std::vector<int> finalVector;
    int nodesCount;
    int solutionDepth;
	//std::vector<Node*> solve(const std::vector<int>& initialVector);
    std::vector<Node*> traceSolution(Node* node);
};

#endif // BFS_H
