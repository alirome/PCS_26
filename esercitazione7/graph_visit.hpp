#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include "grafi.hpp"
#include "contenitori.hpp"

//BFS- profondità lifo stack
//DFS- ampiezza fifo queue

template <typename T>
unidirected_graph graph_visit(const unidirected_graph& G, int sorgente, T& contenitore){
    unidirected_graph albero;
    std::set<int> visitato; //nodi visitati
    contenitore.put(sorgente);
    visitato.insert(sorgente);

    while (!contenitore.empty()){
        int u= contenitore.get(); //prende il prossimo nodo
        for (auto v: G.neighbors(u)){
            if (visitato.find(v)==visitato.end()){
                visitato.insert(v);
                albero.add_edge(u,v);
                contenitore.put(v);
            }
        }
    }
    return albero;

}