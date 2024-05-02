#include "idastar.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <cmath>
#include <chrono>
#include <vector>
#include <climits>

// Implementação do construtor da classe Node
IdaStarNode::IdaStarNode(const std::vector<int>& _state, IdaStarNode* _parent)
    : state(_state), parent(_parent), g_cost(0), h_cost(0), f_cost(0) {}

// Localiza a posição do zero no estado
int IdaStarNode::findZero() const {
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] == 0) {
            return i;
        }
    }
    return -1; // Se não encontrar o zero
}

// Métodos para movimentação do zero
IdaStarNode* IdaStarNode::moveUp() {
    int zero_pos = findZero();
    if (zero_pos >= 3) { // Pode mover para cima
        std::vector<int> new_state = state;
        std::swap(new_state[zero_pos], new_state[zero_pos - 3]);
        return new IdaStarNode(new_state, this);
    }
    return nullptr;
}

IdaStarNode* IdaStarNode::moveLeft() {
    int zero_pos = findZero();
    if (zero_pos % 3 > 0) { // Pode mover para a esquerda
        std::vector<int> new_state = state;
        std::swap(new_state[zero_pos], new_state[zero_pos - 1]);
        return new IdaStarNode(new_state, this);
    }
    return nullptr;
}

IdaStarNode* IdaStarNode::moveRight() {
    int zero_pos = findZero();
    if (zero_pos % 3 < 2) { // Pode mover para a direita
        std::vector<int> new_state = state;
        std::swap(new_state[zero_pos], new_state[zero_pos + 1]);
        return new IdaStarNode(new_state, this);
    }
    return nullptr;
}

IdaStarNode* IdaStarNode::moveDown() {
    int zero_pos = findZero();
    if (zero_pos < 6) { // Pode mover para baixo
        std::vector<int> new_state = state;
        std::swap(new_state[zero_pos], new_state[zero_pos + 3]);
        return new IdaStarNode(new_state, this);
    }
    return nullptr;
}

// Função para calcular a distância Manhattan
int manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal) {
    int distance = 0;
    for (int i = 0; i < state.size(); ++i) {
        if (state[i] != 0) {
            int goal_pos = std::find(goal.begin(), goal.end(), state[i]) - goal.begin();
            int row_distance = std::abs(i / 3 - goal_pos / 3);
            int col_distance = std::abs(i % 3 - goal_pos % 3);
            distance += row_distance + col_distance;
        }
    }
    return distance;
}

// Implementação do construtor da classe IDAStar
IDAStar::IDAStar(const std::vector<int>& _goal_state)
    : goal_state(_goal_state), nodes_expanded(0), nodes_generated(0), heuristic_sum(0), start_heuristic(0) {}

// Função para rastrear o caminho do nó final ao início
std::vector<IdaStarNode*> IDAStar::tracePath(IdaStarNode* node) {
    std::vector<IdaStarNode*> path;
    while (node) {
        path.push_back(node);
        node = node->parent;
         
    }
    std::reverse(path.begin(), path.end()); // Inverte para obter a ordem correta
    return path;
}

// Função recursiva para busca de profundidade limitada
std::pair<int, std::vector<IdaStarNode*>> IDAStar::depthLimitedSearch(
    IdaStarNode* node,
    int g_cost,
    int limit,
    std::unordered_set<std::vector<int>, VectorHash>& visited) {
   	nodes_expanded++;
    heuristic_sum += node->h_cost;
    nodes_generated++;
    int h_cost = manhattanDistance(node->state, goal_state);
    int f_cost = g_cost + h_cost;

    node->g_cost = g_cost;
    node->h_cost = h_cost;
    node->f_cost = f_cost;

    if (f_cost > limit) {
        return {f_cost, {}};  // Se f_cost ultrapassar o limite, retorna o próximo limite
    }

    if (node->state == goal_state) {
        return {INT_MAX, tracePath(node)};  // Se encontrou uma solução
    }

    // Gerar filhos na ordem especificada
    std::vector<IdaStarNode*> children = {
        node->moveUp(),
        node->moveLeft(),
        node->moveRight(),
        node->moveDown(),
    };

    // Remover filhos nulos
    children.erase(
        std::remove_if(children.begin(), children.end(), [](IdaStarNode* child) { return child == nullptr; }), 
        children.end());

    int next_limit = INT_MAX;

    for (IdaStarNode* child : children) {
        if (visited.find(child->state) != visited.end()) {
            nodes_expanded--;
        }

        visited.insert(child->state);

        auto result = depthLimitedSearch(child, g_cost + 1, limit, visited);

        if (!result.second.empty()) {  // Se uma solução foi encontrada
            return result;
        }
        next_limit = std::min(next_limit, result.first);

        delete child;  // Limpeza para evitar vazamentos de memória
    }

    return {next_limit, {}};  // Retorna o próximo limite
}

// Implementação do método para busca IDA*
std::vector<IdaStarNode*> IDAStar::idaStar(const std::vector<int>& initial_state) {
    start_heuristic = manhattanDistance(initial_state, goal_state);

    IdaStarNode* initial_node = new IdaStarNode(initial_state);
    initial_node->h_cost = start_heuristic;

    int limit = start_heuristic;
    std::vector<IdaStarNode*> solution_path;
    std::unordered_set<std::vector<int>, VectorHash> visited;

    while (solution_path.empty()) { 
        visited.insert(initial_node->state);

        auto result = depthLimitedSearch(initial_node, 0, limit, visited);
        
        if (!result.second.empty()) {
            solution_path = result.second;  // Solução encontrada
        } else {
            limit = result.first;  // Atualiza o limite para próxima iteração
        }
    }

    return solution_path;  // Retorna o caminho para a solução
}

// Métodos para obter informações do IDAStar
int IDAStar::getNodesExpanded() const {
    return nodes_expanded;
}

int IDAStar::getNodesGenerated() const {
    return nodes_generated;
}

int IDAStar::getHeuristicSum() const {
    return heuristic_sum;
}

int IDAStar::getStartHeuristic() const {
    return start_heuristic;
}
