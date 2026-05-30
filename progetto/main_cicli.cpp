#include <iostream>
#include "graphs.hpp"
#include "contenitori.hpp"
#include "cicli_fondamentali.hpp"

int main() {
    // Grafo di test:
    //
    //   0 ---5--- 1
    //   |        /|
    //   3       4 2
    //   |      /  |
    //   3 ---1--- 2
    //
    // Nodi: 0, 1, 2, 3
    // Archi: (0,1) peso 5
    //        (0,3) peso 3
    //        (1,2) peso 2
    //        (2,3) peso 1
    //        (1,3) peso 4
    //
    // |E| = 5, |V| = 4  →  cicli fondamentali attesi = 5 - 4 + 1 = 2

    unidirected_graph<int> G;
    G.add_edge(0, 1, 5);
    G.add_edge(0, 3, 3);
    G.add_edge(1, 2, 2);
    G.add_edge(2, 3, 1);
    G.add_edge(1, 3, 4);

    std::cout << "=== Grafo di test ===" << std::endl;
    std::cout << "Archi:" << std::endl;
    for (const auto& e : G.all_edges())
        std::cout << "  " << e << " peso=" << G.weight(e.from(), e.to()) << std::endl;

    // Calcola cicli fondamentali con DFS
    std::cout << "\n=== Cicli fondamentali (DFS) ===" << std::endl;
    auto cicli = cicli_fondamentali_dfs(G, 0);

    std::cout << "Trovati " << cicli.size() << " cicli (attesi 2)" << std::endl;

    for (size_t i = 0; i < cicli.size(); ++i) {
        std::cout << "\nCiclo " << i << ":" << std::endl;

        std::cout << "  Nodi nel path: ";
        for (int n : cicli[i].nodes)
            std::cout << n << " ";
        std::cout << std::endl;

        std::cout << "  Archi: ";
        for (const auto& e : cicli[i].edges)
            std::cout << e << " ";
        std::cout << std::endl;
    }

    return 0;
}
