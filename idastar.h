#ifndef IDASTAR_H
#define IDASTAR_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cmath>

using namespace std;

// Estrutura para hash de vetores de inteiros
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t hash = 0;
        for (int i : v) {
            hash ^= std::hash<int>{}(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

// Declaração da classe Node para representar os estados do quebra-cabeça
class IdaStarNode {
public:
    vector<int> state;
    IdaStarNode* parent;
    int g_cost;
    int h_cost;
    int f_cost;

    IdaStarNode(const vector<int>& _state, IdaStarNode* _parent = nullptr);

    int findZero() const; // Localiza a posição do zero no estado
    IdaStarNode* moveUp(); // Move para cima, se possível
    IdaStarNode* moveLeft(); // Move para a esquerda, se possível
    IdaStarNode* moveRight(); // Move para a direita, se possível
    IdaStarNode* moveDown(); // Move para baixo, se possível
};

// Função para calcular a distância Manhattan
int manhattanDistance(const vector<int>& state, const vector<int>& goal);

// Declaração da classe IDAStar
class IDAStar {
public:
    vector<int> goal_state; // Estado objetivo do quebra-cabeça
    int nodes_expanded; // Número de nós expandidos
    int nodes_generated; // Número de nós gerados
    int heuristic_sum; // Soma das heurísticas
    int start_heuristic; // Heurística do estado inicial

    IDAStar(const vector<int>& _goal_state);

    // Função para rastrear o caminho do nó final ao início
    vector<IdaStarNode*> tracePath(IdaStarNode* node);

    // Função recursiva para busca de profundidade limitada
    pair<int, vector<IdaStarNode*>> depthLimitedSearch(IdaStarNode* node, int g_cost, int limit, unordered_set<vector<int>, VectorHash>& visited);

    // Função para iniciar a busca IDA*
    vector<IdaStarNode*> idaStar(const vector<int>& initial_state);

    int getNodesExpanded() const; // Retorna o número de nós expandidos
    int getNodesGenerated() const; // Retorna o número de nós gerados
    int getHeuristicSum() const; // Retorna a soma das heurísticas
    int getStartHeuristic() const; // Retorna a heurística do estado inicial
};

#endif // IDASTAR_H
