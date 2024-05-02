#ifndef GBFS_H
#define GBFS_H

#include "gbfsnode.h"
#include "node.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

class GBFS {
public:
    GBFS(const std::vector<int>& finalVector);

    std::vector<Node*> solve(const std::vector<int>& initialVector);

    int getNodesCount() const;
    double getHeuristicAverage() const;
    int getStartHeuristic() const;

private:
    std::vector<int> finalVector;
    int nodesCount;
    double heuristicSum;
    int startHeuristic;

    int manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal);
    std::vector<Node*> tracePath(Node* node);
};

#endif // GBFS_H
