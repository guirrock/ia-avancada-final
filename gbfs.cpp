#include "gbfs.h" // Inclui o cabeçalho com a definição de classes e funções necessárias para GBFS
#include <algorithm> // Inclui funcionalidades como 'std::find' e 'std::reverse'

// Construtor da classe GBFS, inicializa variáveis de estado com o vetor final e outras variáveis para estatísticas
GBFS::GBFS(const std::vector<int>& finalVector)
    : finalVector(finalVector), nodesCount(0), heuristicSum(0), startHeuristic(0) {}

// Retorna o número de nós expandidos durante a busca
int GBFS::getNodesCount() const {
    return nodesCount;
}

// Retorna a média dos valores heurísticos dos nós expandidos, garantindo que não haja divisão por zero
double GBFS::getHeuristicAverage() const {
    return (nodesCount > 0) ? (heuristicSum / nodesCount) : 0.0;
}

// Retorna o valor heurístico do estado inicial
int GBFS::getStartHeuristic() const {
    return startHeuristic;
}

// Calcula a distância de Manhattan entre um estado atual e um estado objetivo
int GBFS::manhattanDistance(const std::vector<int>& state, const std::vector<int>& goal) {
    int distance = 0; // Inicializa a distância em zero
    // Percorre cada elemento do vetor de estado para calcular a distância de Manhattan
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) { // Ignora o espaço vazio
            // Determina a posição correspondente no vetor objetivo
            int goalPos = static_cast<int>(std::distance(goal.begin(), std::find(goal.begin(), goal.end(), state[i])));
            // Calcula a diferença de linhas
            int rowDistance = std::abs(static_cast<int>(i / 3) - (goalPos / 3));
            // Calcula a diferença de colunas
            int colDistance = std::abs(static_cast<int>((i % 3) - (goalPos % 3)));
            distance += rowDistance + colDistance; // Soma as distâncias de linha e coluna
        }
    }
    return distance; // Retorna a distância total calculada
}

// Traça o caminho a partir de um nó até a raiz, gerando uma lista de nós
std::vector<Node*> GBFS::tracePath(Node* node) {
    std::vector<Node*> path; // Cria um vetor para armazenar o caminho
    // Continua subindo pelos pais até chegar ao início
    while (node) {
        path.push_back(node); // Adiciona o nó ao caminho
        node = node->parent; // Move para o nó pai
    }
    std::reverse(path.begin(), path.end()); // Reverte a ordem para ter o caminho do início ao fim
    return path; // Retorna o caminho completo
}

// Resolve o problema usando a busca greedy best-first
std::vector<Node*> GBFS::solve(const std::vector<int>& initialVector) {
    // Usa uma fila de prioridade para escolher o nó com menor heurística
    std::priority_queue<GBFSNode, std::vector<GBFSNode>, GBFSComparator> openList;
    // Usa um conjunto para armazenar estados já visitados para evitar loops
    std::unordered_set<std::string> closedSet;

    // Cria o nó inicial sem pai e com custo de passo inicial de 1
    Node* startNode = new Node(initialVector, nullptr, 1);
    int insertionCounter = 1; // Contador para atribuir IDs aos nós

    // Define o custo G inicial (custo do caminho) e o custo H inicial (heurística)
    int startGCost = 0; // Custo do caminho do início até agora
    int startHCost = manhattanDistance(initialVector, finalVector); // Calcula a heurística do estado inicial
    startHeuristic = startHCost; // Armazena a heurística inicial

    // Insere o nó inicial na fila de prioridade com custos G e H
    openList.push({startNode, startGCost, startHCost});

    // Continua a busca enquanto houver nós na fila
    while (!openList.empty()) {
        // Obtém o nó com menor heurística da fila
        GBFSNode currentGBFSNode = openList.top();
        openList.pop(); // Remove o nó da fila

        Node* currentNode = currentGBFSNode.node; // O nó atual para explorar

        // Converte o estado atual para uma string para facilitar a comparação no conjunto
        std::string stateStr;
        for (int i : currentNode->initialVector) {
            stateStr += std::to_string(i) + ","; // Converte cada valor para string
        }

        // Se o estado atual já foi visitado, pula para o próximo nó
        if (closedSet.count(stateStr) > 0) {
            continue; // Ignora estados já visitados
        }

        // Adiciona o estado atual ao conjunto de estados visitados
        closedSet.insert(stateStr);

        // Se o estado atual é o objetivo, traça o caminho e retorna
        if (currentNode->initialVector == finalVector) {
            return tracePath(currentNode); // Retorna o caminho completo
        }

        // Aumenta o contador de inserções para geração de IDs exclusivos
        insertionCounter++;
        nodesCount++; // Incrementa o contador de nós expandidos
        heuristicSum += currentGBFSNode.hCost; // Acumula o valor heurístico

        // Gera novos movimentos para cima, esquerda, direita e para baixo
        currentNode->moveUp(insertionCounter++);
        currentNode->moveLeft(insertionCounter++);
        currentNode->moveRight(insertionCounter++);
        currentNode->moveDown(insertionCounter++);

        // Para cada nó filho gerado, verifica se ele já foi visitado
        for (Node* child : currentNode->children) {
            std::string childStateStr;
            for (int i : child->initialVector) {
                childStateStr += std::to_string(i) + ","; // Cria a string do estado do filho
            }

            // Se o filho já foi visitado, pula para o próximo
            if (closedSet.count(childStateStr) > 0) {
                continue; // Ignora estados visitados
            }

            // Calcula o custo G e o custo H para o nó filho
            int gCost = currentGBFSNode.gCost + 1; // Custo do caminho para o nó filho
            int hCost = manhattanDistance(child->initialVector, finalVector); // Heurística para o nó filho

            // Adiciona o filho à fila de prioridade para exploração futura
            openList.push({child, gCost, hCost});
        }
    }

    return {}; // Retorna um vetor vazio se nenhum caminho foi encontrado
}
