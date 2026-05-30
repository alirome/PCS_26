#include <iostream>
#include "graphs.hpp"
#include "contenitori.hpp"
#include "DePina.hpp"

int main() {
    // Grafo di test:
    //
    //   0 ---5--- 1
    //   |         |
    //   3         2
    //   |         |
    //   3 ---1--- 2
    //        |
    //        4 (arco diagonale 1-3, peso 4)
    //
    // Nodi: 0, 1, 2, 3
    // Archi: (0,1) peso 5
    //        (0,3) peso 3
    //        (1,2) peso 2
    //        (2,3) peso 1
    //        (1,3) peso 4  ← arco extra che chiude un secondo ciclo
    //
    // |E| = 5, |V| = 4  →  cicli fondamentali = 5 - 4 + 1 = 2

    unidirected_graph<int> G;
    G.add_edge(0, 1, 5);
    G.add_edge(0, 3, 3);
    G.add_edge(1, 2, 2);
    G.add_edge(2, 3, 1);
    G.add_edge(1, 3, 4);

    std::cout << "=== Grafo di test ===" << std::endl;
    std::cout << "Nodi: ";
    for (int n : G.all_nodes()) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "Archi (con indice e peso):" << std::endl;
    for (const auto& e : G.all_edges()) {
        std::cout << "  [" << G.edge_number(e) << "] "
                  << e << " peso=" << G.weight(e.from(), e.to())
                  << std::endl;
    }

    // Calcola cicli minimi con De Pina
    std::cout << "\n=== De Pina ===" << std::endl;
    std::vector<std::vector<bool>> cicli = de_pina(G, 0);

    std::cout << "Trovati " << cicli.size() << " cicli (attesi 2)" << std::endl;

    for (size_t i = 0; i < cicli.size(); ++i) {
        std::cout << "\nCiclo " << i << ": ";
        bool vuoto = true;
        for (size_t j = 0; j < cicli[i].size(); ++j) {
            if (cicli[i][j]) {
                auto e = G.edge_at(j);
                std::cout << e << " ";
                vuoto = false;
            }
        }
        if (vuoto) std::cout << "(errore: cammino vuoto)";
        std::cout << std::endl;
    }

    // Verifica manuale attesa:
    // Ciclo minimo 1: (0,3) + (2,3) + (1,2) + (1,3) peso = 3+1+2+4 = 10? 
    // oppure (2,3) + (1,2) + (1,3) peso = 1+2+4 = 7
    // Ciclo minimo 2: (0,1) + (0,3) + (1,3) peso = 5+3+4 = 12?
    // I cicli esatti dipendono dall'albero DFS scelto — l'importante
    // e' che siano 2 cicli non vuoti e indipendenti.

    return 0;
}