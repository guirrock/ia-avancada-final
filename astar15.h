#ifndef ASTAR15_H
#define ASTAR15_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <cmath>
#include <string>

class A15Node {
public:
    std::vector<int> initialVector;
    A15Node* parent;
    int insertionOrder;
    std::vector<A15Node*> children;

    A15Node(std::vector<int> _initialVector, A15Node* _parent, int _insertionOrder);

    int findZero() const; // Localiza a posição do zero
    void printPuzzle() const; // Imprime o estado do puzzle
    void moveUp(int order); // Move para cima
    void moveDown(int order); // Move para baixo
    void moveLeft(int order); // Move para a esquerda
    void moveRight(int order); // Move para a direita
};

class AstarNode15 {
public:
    A15Node* node;
    int gCost;
    int hCost;
    int fCost;

    AstarNode15(A15Node* _node, int _gCost, int _hCost, int _fCost);
};

struct AstarComparator15 {
    bool operator()(const AstarNode15& a, const AstarNode15& b) const; // Comparador para a fila de prioridade
};

// Função para rastrear o caminho do nó final ao início
std::vector<A15Node*> tracePath(A15Node* node);

// Função para calcular a distância Manhattan
int manhattanDistanceA15(const std::vector<int>& state, const std::vector<int>& goal);

class A15Puzzle {
private:
    std::vector<int> finalVector; // O estado final do 15-puzzle

public:
    int nodesCount = 0; // Número de nós expandidos
    float heuristicSum = 0; // Soma das heurísticas
    int startHeuristic = 0; // Heurística do estado inicial

    A15Puzzle(std::vector<int> _finalVector);

    std::vector<A15Node*> Astar15(const std::vector<int>& initialVector); // Método para execução do algoritmo A*
};

#endif // ASTAR15_H
