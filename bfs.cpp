#include "bfs.h" // Inclui o cabeçalho contendo a declaração da classe BFS
#include <algorithm> // Para usar std::reverse para reverter um vetor

BFS::BFS(const std::vector<int>& finalVector) 
    : finalVector(finalVector), nodesCount(0), solutionDepth(0) {} 
// Construtor da classe BFS. Recebe um vetor que representa o estado final 
// e inicializa os atributos `nodesCount` e `solutionDepth` com zero.

int BFS::getNodesCount() const { 
    return nodesCount; 
}
// Função para retornar a contagem total de nós visitados durante a busca.

int BFS::getSolutionDepth() const { 
    return solutionDepth; 
}
// Função para retornar a profundidade da solução encontrada.

std::vector<Node*> BFS::traceSolution(Node* node) { 
    std::vector<Node*> path; // Cria um vetor para armazenar o caminho da solução
    while (node) { // Enquanto houver um nó válido
        path.push_back(node); // Adiciona o nó atual ao caminho
        node = node->parent; // Segue para o nó pai
    }
    std::reverse(path.begin(), path.end()); // Inverte o vetor para ter o caminho na ordem correta
    return path; // Retorna o caminho completo
}

std::vector<Node*> BFS::solve(const std::vector<int>& initialVector) { 
    Node* initialNode = new Node(initialVector, nullptr, 1); 
    // Cria um nó inicial usando o vetor inicial, sem pai, e com profundidade 1
    
    BFSNode bfsNode(initialNode); 
    // Cria um objeto auxiliar para a BFS, a partir do nó inicial

    std::vector<Node*> solutionPath; // Cria um vetor para armazenar o caminho da solução encontrada
    
    // Enquanto houver nós para visitar
    while (Node* currentNode = bfsNode.getNextNode()) { 
        currentNode->moveUp(1); // Move para cima (ou tenta, com valor 1)
        currentNode->moveLeft(1); // Move para a esquerda
        currentNode->moveRight(1); // Move para a direita
        currentNode->moveDown(1); // Move para baixo

        nodesCount++; // Incrementa a contagem de nós visitados

        // Para cada nó filho gerado a partir do nó atual
        for (Node* child : currentNode->children) {
            // Se um nó filho tiver o vetor igual ao vetor final, encontrou-se a solução
            if (child->initialVector == finalVector) { 
                solutionPath = traceSolution(child); 
                // Traça o caminho de volta para obter a solução
                solutionDepth = static_cast<int>(solutionPath.size()); 
                // Define a profundidade da solução encontrada
                return solutionPath; // Retorna o caminho da solução
            }

            // Se o vetor do filho não foi visitado antes
            if (!bfsNode.isVisited(child->initialVector)) { 
                bfsNode.addNode(child); // Adiciona o nó ao BFSNode para futura visita
                bfsNode.setVisited(child->initialVector); 
                // Marca este vetor como visitado
            }
        }
    }

    return {}; // Se nenhum caminho foi encontrado, retorna um vetor vazio
}
