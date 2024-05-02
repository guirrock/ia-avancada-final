#ifndef ASTAR_H
#define ASTAR_H

#include "node.h"
#include "astarnode.h"
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <algorithm>

class Astar {
public:
    Astar(const std::vector<int>& finalVector);
    std::vector<Node*> findSolution(const std::vector<int>& initialVector);

    int getNodesCount() const;
    float getHeuristicAverage() const;
    int getStartHeuristic() const;

private:
    std::vector<int> finalVector;
    int nodesCount;
    float heuristicSum;
    int startHeuristic;

    int manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal);
    std::vector<Node*> tracePath(Node* node);
};

#endif // ASTAR_H
