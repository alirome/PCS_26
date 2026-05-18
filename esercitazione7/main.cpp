#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include "grafi.hpp"
#include "contenitori.hpp"
#include "graph_visit.hpp"
#include "recursive_dfs.hpp"
#include "Dijkstra.hpp"
#include <fstream>

//per i grafici https://edotor.net/

int main(){

    unidirected_graph G;
    G.add_edge(1,2);
    G.add_edge(1,3);
    G.add_edge(1,6);
    G.add_edge(2,5);
    G.add_edge(3,6);
    G.add_edge(2,4);
    G.add_edge(4,7);
    G.add_edge(4,6);
    G.add_edge(5,7);
    G.add_edge(6,8);
    G.add_edge(7,9);
    G.add_edge(8,9);
    
    std::cout<< "grafico G:\n";
    G.to_dot(std::cout);

    lifo<int> s;
    auto dfsG= graph_visit(G, 1, s);

    std::cout<< "grafico dfsG:\n";
    dfsG.to_dot(std::cout);

    fifo<int> q;
    auto bfsG= graph_visit(G, 1, q);

    std::cout<< "grafico bfsG:\n";
    bfsG.to_dot(std::cout);

    auto albero_ricorsivo= recursive_dfs(G,1);

    std::cout<< "grafico ricorsivo:\n";
    albero_ricorsivo.to_dot(std::cout);

    int n=G.all_nodes().size();
    int max_nodo=9; 
    //creo la matrice dei pesi ammettendoli tutti =1 per comodità
    std::vector<std::vector<int>> W(max_nodo + 1, std::vector<int>(max_nodo + 1, 1));

    auto albero_dijkstra= Dijkstra(G, W, 1, n);

    std::cout<< "grafico dijkstra:\n";
    albero_dijkstra.to_dot(std::cout);
};


//std::ofstream outfile_d("dfs_result.dot");
//dfsG.to_dot(outfile_d);
//outfile_d.close();