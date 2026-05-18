#pragma once
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "grafi.hpp"

void ricorsione(const unidirected_graph& G, int u, std::set<int>& visitato, unidirected_graph& albero){
    visitato.insert(u);
    for (auto v: G.neighbors(u)){ //backtracking
        if (visitato.find(v)== visitato.end()){
            albero.add_edge(u,v);
            ricorsione(G,v,visitato,albero);
        }
    }
}

unidirected_graph recursive_dfs(const unidirected_graph& G, int sorgente){
    unidirected_graph albero;
    std::set<int> visitato;
    ricorsione(G, sorgente, visitato, albero);
    return albero;
}