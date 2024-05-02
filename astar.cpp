#include "astar.h"

// Construtor para a classe Astar, que inicializa os valores do vetor final,
// a contagem de nós, a soma das heurísticas e a heurística inicial.
Astar::Astar(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), heuristicSum(0), startHeuristic(0) {}

// Retorna a contagem de nós que foram visitados durante a execução do algoritmo.
int Astar::getNodesCount() const {
    return nodesCount;
}

// Retorna a média das heurísticas para todos os nós processados.
float Astar::getHeuristicAverage() const {
    // Se nenhum nó foi processado, retorna 0 para evitar divisão por zero.
    return (nodesCount > 0) ? (heuristicSum / nodesCount) : 0.0f;
}

// Retorna a heurística do nó inicial.
int Astar::getStartHeuristic() const {
    return startHeuristic;
}

// Calcula a distância de Manhattan entre dois vetores de estado (geralmente usados para representar um quebra-cabeça 3x3).
int Astar::manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal) {
    int distance = 0; // Inicializa a distância como zero
    // Para cada elemento do estado, calcula a posição correspondente no vetor do objetivo
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) { // Ignora o espaço vazio (geralmente representado por 0)
            // Encontra a posição do elemento no vetor objetivo
            int goalPos = static_cast<int>(std::distance(goal.begin(), std::find(goal.begin(), goal.end(), state[i])));
            // Calcula a diferença de linha e coluna
            int rowDistance = std::abs(static_cast<int>(i / 3) - static_cast<int>(goalPos / 3));
            int colDistance = std::abs(static_cast<int>(i % 3) - static_cast<int>(goalPos % 3));
            // Soma a distância de linha e coluna para obter a distância de Manhattan
            distance += rowDistance + colDistance;
        }
    }
    return distance; // Retorna a distância de Manhattan total
}

// Recria o caminho do nó final até o nó inicial, passando por cada nó pai.
std::vector<Node*> Astar::tracePath(Node* node) {
    std::vector<Node*> path; // Cria um vetor para armazenar o caminho
    // Enquanto existir um nó pai, adiciona ao caminho e avança para o nó pai
    while (node) {
        path.push_back(node); // Adiciona o nó atual ao caminho
        node = node->parent; // Move para o nó pai
    }
    // Inverte o caminho para ficar do início ao fim
    std::reverse(path.begin(), path.end());
    return path; // Retorna o caminho completo
}

// Encontra a solução para um quebra-cabeça utilizando o algoritmo A*.
std::vector<Node*> Astar::findSolution(const std::vector<int>& initialVector) {
    // Cria uma fila de prioridade para o algoritmo A*, comparando pelo custo F (g + h)
    std::priority_queue<AstarNode, std::vector<AstarNode>, AstarComparator> openList;
    std::unordered_set<std::string> closedSet; // Conjunto para evitar reprocessamento de nós
    int insertionCounter = 0; // Contador para ajudar no processo de inserção dos nós

    // Cria o nó inicial a partir do vetor inicial, sem nó pai e com incremento do contador
    Node* startNode = new Node(initialVector, nullptr, insertionCounter++);
    // Calcula o custo g, h e f para o nó inicial
    int startGCost = 0; // Custo para chegar ao nó inicial (0, pois é o ponto de partida)
    int startHCost = manhattanDistance(initialVector, finalVector); // Calcula a distância de Manhattan para a heurística
    int startFCost = startGCost + startHCost; // Custo F é a soma de g + h

    // Insere o nó inicial na lista aberta com seus custos g, h e f
    openList.push({ startNode, startGCost, startHCost, startFCost });
    startHeuristic = startHCost; // Define a heurística inicial para futura referência

    // Enquanto houver nós na lista aberta, o algoritmo A* continuará processando
    while (!openList.empty()) {
        // Recupera o nó com menor custo f (cabeça da lista) e o remove
        AstarNode currentAstarNode = openList.top();
        openList.pop();

        Node* currentNode = currentAstarNode.node; // O nó atual para processamento

        std::string stateStr; // Armazena a representação em string do estado do nó
        for (int i : currentNode->initialVector) { // Converte o vetor de estado para string
            stateStr += std::to_string(i) + ",";
        }

        // Se o estado do nó já está no conjunto fechado, pulamos para o próximo nó
        if (closedSet.count(stateStr) > 0) {
            continue; // Pula a iteração atual
        }

        // Adiciona o estado atual ao conjunto fechado para evitar reprocessamento
        closedSet.insert(stateStr);

        // Se o vetor de estado do nó atual é igual ao vetor final, o quebra-cabeça está resolvido
        if (currentNode->initialVector == finalVector) {
            // Traça o caminho do nó final até o nó inicial e o retorna como solução
            return tracePath(currentNode);
        }

        nodesCount++; // Incrementa a contagem de nós processados
        heuristicSum += currentAstarNode.hCost; // Soma a heurística do nó atual

        // Gera os nós filhos (movimentos válidos no quebra-cabeça)
        currentNode->moveUp(insertionCounter++); // Move para cima
        currentNode->moveLeft(insertionCounter++); // Move para a esquerda
        currentNode->moveRight(insertionCounter++); // Move para a direita
        currentNode->moveDown(insertionCounter++); // Move para baixo

        // Para cada nó filho gerado, verifica se ele já foi processado
        for (Node* child : currentNode->children) {
            std::string childStateStr; // Representação em string do estado do filho
            for (int i : child->initialVector) {
                childStateStr += std::to_string(i) + ",";
            }

            // Se o estado do filho já está no conjunto fechado, pula para o próximo filho
            if (closedSet.count(childStateStr) > 0) {
                continue; // Pula a iteração atual
            }

            // Calcula custos g, h e f para o nó filho
            int gCost = currentAstarNode.gCost + 1; // Custo g é o custo do nó pai + 1 (movimento)
            int hCost = manhattanDistance(child->initialVector, finalVector); // Heurística do filho
            int fCost = gCost + hCost; // Custo F é a soma de g + h

            // Adiciona o nó filho na lista aberta para ser processado depois
            openList.push({ child, gCost, hCost, fCost });
        }
    }

    return {}; // Se nenhum caminho foi encontrado, retorna um vetor vazio
}
