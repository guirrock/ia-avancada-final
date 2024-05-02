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
#include <cstring> // Para comparar strings C

int main(int argc, char* argv[]) {
    if (argc < 2) { // Verifica se ao menos um argumento foi fornecido
        std::cerr << "Uso: " << argv[0] << " <algoritmo>\n";
        std::cerr << "Algoritmos disponíveis: -bfs, -gbfs, -astar, -idastar\n";
        return 1; // Retorna erro se nenhum argumento for fornecido
    }

    std::string algoritmo = argv[1]; // Obtém o argumento do algoritmo

    if (algoritmo != "-bfs" && algoritmo != "-gbfs" && algoritmo != "-astar" && algoritmo != "-idastar" && algoritmo != "-idfs" && algoritmo != "-astar15") {
        std::cerr << "Algoritmo não reconhecido. Use '-bfs', '-gbfs', '-idfs', '-astar15', '-idastar' ou '-astar'.\n";
        return 1; // Retorna erro se o argumento não for um dos algoritmos esperados
    }



    std::ifstream inputFile("input/8puzzle_instances.txt"); // Abre o arquivo de entrada

	std::ifstream inputFile2("input/15puzzle_instances.txt"); // Abre o arquivo de entrada


    if (!inputFile.is_open()) { 
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1; // Retorna erro se não conseguir abrir o arquivo
    }
    if (!inputFile2.is_open()) { 
        std::cerr << "Erro ao abrir o arquivo de entrada." << std::endl;
        return 1; // Retorna erro se não conseguir abrir o arquivo
    }

    std::string line; 
    std::vector<std::vector<int>> initialStates;
	std::vector<std::vector<int>> initialStates2;
    // Lê os estados iniciais do arquivo
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::vector<int> initialState;
        int num;

        while (iss >> num) {
            initialState.push_back(num);
        }

        initialStates.push_back(initialState); // Adiciona o estado inicial ao vetor
    }
    
     // Lê os estados iniciais do arquivo
    while (std::getline(inputFile2, line)) {
        std::istringstream iss(line);
        std::vector<int> initialState2;
        int num;

        while (iss >> num) {
            initialState2.push_back(num);
        }

        initialStates2.push_back(initialState2); // Adiciona o estado inicial ao vetor
    }

    inputFile.close(); // Fecha o arquivo

    std::vector<int> finalState = {0, 1, 2, 3, 4, 5, 6, 7, 8}; // Estado final do 8-puzzle
    std::vector<int> finalState15 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // Estado final do 15-puzzle

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
        } else if (algoritmo == "-bfs") {
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
        	
		IDFSPuzzle puzzle(initialState, finalState15);
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
    	}
		
    }
     for (const auto& initialState2 : initialStates2) {
	 
	 if (algoritmo == "-astar15") { // Novo caso para A* do 15-puzzle
            A15Puzzle puzzle(finalState15); // Alvo do 15-puzzle
            auto start_time = std::chrono::high_resolution_clock::now();

            auto solutionPath = puzzle.Astar15(initialState2);

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

