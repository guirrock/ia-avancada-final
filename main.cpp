#include "astar.h"
#include "gbfs.h"
#include "bfs.h"
#include "idfs.h"
#include "idastar.h"
#include "astar15.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>
#include <cstring>

bool isValidPuzzleState(const std::vector<int>& state, int puzzleSize) {
    if (state.size() != puzzleSize) {
        return false;
    }

    std::vector<int> counts(puzzleSize, 0);
    for (int val : state) {
        if (val < 0 || val >= puzzleSize) {
            return false;
        }
        counts[val]++;
    }

    for (int count : counts) {
        if (count != 1) {
            return false;
        }
    }

    return true;
}

void parseInputStates(const std::string& input, std::vector<std::vector<int>>& states, int puzzleSize) {
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {  // Para cada estado inicial separado por vírgulas
        std::vector<int> state;
        std::istringstream stateStream(token);
        int value;

        while (stateStream >> value) {  // Extrai os valores separados por espaços
            state.push_back(value);
        }

        if (isValidPuzzleState(state, puzzleSize)) {
            states.push_back(state);
        } else {
            std::cerr << "Estado inválido: " << token << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <algoritmo> [lista_de_estados]\n";
        std::cerr << "Algoritmos disponíveis: -bfs, -gbfs, -astar, -idastar, -idfs, -astar15\n";
        return 1;
    }

    std::string algoritmo = argv[1];
    int puzzleSize = 9;  // Por padrão, assume 8-puzzle

    if (algoritmo == "-astar15") {
        puzzleSize = 16;
    }

    if (algoritmo != "-bfs" && algoritmo != "-gbfs" && algoritmo != "-astar" && algoritmo != "-idastar" && algoritmo != "-idfs" && algoritmo != "-astar15") {
        std::cerr << "Algoritmo não reconhecido. Use '-bfs', '-gbfs', '-idfs', '-astar15', '-idastar', ou '-astar'.\n";
        return 1;
    }

    std::vector<std::vector<int>> initialStates;

    if (argc > 2) {
        std::string allStates;
        // Junta todos os argumentos a partir do 2º, para permitir espaços entre números
        for (int i = 2; i < argc; i++) {
            if (i > 2) {
                allStates += " ";  // Adiciona espaço entre argumentos
            }
            allStates += argv[i];
        }
        
        parseInputStates(allStates, initialStates, puzzleSize);  // Processa como um bloco único
    } else {
        std::string inputFileName = (algoritmo == "-astar15") ? "input/15puzzle_instances.txt" : "input/8puzzle_instances.txt";

        std::ifstream inputFile(inputFileName);
        if (!inputFile.is_open()) {
            std::cerr << "Erro ao abrir o arquivo " << inputFileName << "." << std::endl;
            return 1;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::vector<int> state;
            std::istringstream iss(line);
            int num;
            while (iss >> num) {
                state.push_back(num);
            }

            if (isValidPuzzleState(state, puzzleSize)) {
                initialStates.push_back(state);
            } else {
                std::cerr << "Estado inválido encontrado no arquivo." << std::endl;
            }
        }
    }

    if (initialStates.empty()) {
        std::cerr << "Nenhum estado inicial válido encontrado." << std::endl;
        return 1;
    }

    std::vector<int> finalState = (puzzleSize == 16) ? std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} : std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8};

    // A partir daqui, o código para resolver os puzzles usando os algoritmos corretos conforme antes
    for (const auto& initialState : initialStates) {
        
		
		if (algoritmo == "-astar") {
            Astar astar(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = astar.findSolution(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "A*: " << astar.getNodesCount() << ", " << (solutionPath.size() - 1) << ", " 
                          << duration_sec << ", " << astar.getHeuristicAverage() << ", " 
                          << astar.getStartHeuristic() << std::endl;
            } else {
                std::cout << "A*: Nenhuma solução encontrada." << std::endl;
            }
        } else if (algoritmo == "-gbfs") {
            GBFS gbfs(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = gbfs.solve(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "GBFS: " << gbfs.getNodesCount() << ", " << (solutionPath.size() - 1) << ", " 
                          << duration_sec << ", " << gbfs.getHeuristicAverage() << ", " 
                          << gbfs.getStartHeuristic() << std::endl;
            } else {
                std::cout << "GBFS: Nenhuma solução encontrada." << std::endl;
            }
        }else if (algoritmo == "-bfs") {
            BFS bfs(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();
            auto solutionPath = bfs.solve(initialState);
            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "BFS: " << bfs.getNodesCount() << ", " << (solutionPath.size() - 1) << ", " 
                          << duration_sec << ", 0, " 
                          << bfs.getSolutionDepth() << std::endl;
            } else {
                std::cout << "BFS: Nenhuma solução encontrada." << std::endl;
            }
        }else if (algoritmo == "-idastar") { // Adicione a lógica do IDA*
            IDAStar idaStar(finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = idaStar.idaStar(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
            	int a = idaStar.getNodesExpanded();
            	float b = idaStar.heuristic_sum;
                std::cout << "IDA*: " << idaStar.getNodesExpanded() << ", " 
                          << (solutionPath.size() - 1) << ", " 
                          << duration_sec << ", " 
                          <<  b/a << ", " 
                          << idaStar.getStartHeuristic() << std::endl;
            } else {
                std::cout << "IDA*: Nenhuma solução encontrada." << std::endl;
            }
        }else if(algoritmo == "-idfs"){
        	
		IDFSPuzzle puzzle(initialState, finalState);
            auto start_time = std::chrono::high_resolution_clock::now();

            int depth = puzzle.IDFS(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            double duration_sec = std::chrono::duration<double>(end_time - start_time).count();
			int distanceManhattan = manhattanDistanceIDFS(initialState, finalState);
			
            if (depth != -1) {
                std::cout << "IDFS: " << puzzle.nodesCount << ", " << depth - 1 << ", " 
                          << duration_sec << ", " 
                          << "0, " << distanceManhattan << endl; 


            } else {
                std::cout << "IDFS: Nenhuma solução encontrada." << std::endl;
            }
    	
		
    }else if (algoritmo == "-astar15") { // Novo caso para A* do 15-puzzle
            A15Puzzle puzzle(finalState); // Alvo do 15-puzzle
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = puzzle.Astar15(initialState);

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration_sec = std::chrono::duration<double>(end_time - start_time).count();

            if (!solutionPath.empty()) {
                std::cout << "Astar15: " << puzzle.nodesCount << ", " 
                          << (solutionPath.size() - 1) << ", " 
                          << duration_sec << ", " 
                          << puzzle.heuristicSum / puzzle.nodesCount << ", "
                          << puzzle.startHeuristic << endl;
            } else {
                std::cout << "Astar15: Nenhuma solução encontrada." << std::endl;
            }
        }
	 
	 }

    return 0; // Indica que o programa terminou com sucesso
}

