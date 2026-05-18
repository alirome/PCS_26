#pragma once
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "grafi.hpp"

// W=matrice di pesi
unidirected_graph Dijkstra(const unidirected_graph& grafo, const std::vector<std::vector<int>>& W, int sorgente, int n) {
    
    //array dei predecessori
    std::vector<int> predecessori(n, -1);
    const int INF = 1e9;
    //array delle distanze
    std::vector<int> distanza(n, INF);

    predecessori[sorgente] = sorgente;    
    distanza[sorgente] = 0;

    // Coda con priorità
    std::priority_queue<std::pair<int,int>> pq;
    pq.push({0, sorgente}); //enqueue

    while(!pq.empty()) {
        int d = -pq.top().first;
        int u = pq.top().second;
        pq.pop(); //dequeue
        
        //sostituisce il DecreaseKey
        if (d > distanza[u]) 
        continue;

        // Cambiato in 'neighbors' coerentemente con i metodi precedenti
        for (int w : grafo.neighbors(u)) { 
            if (distanza[w] > distanza[u] + W[u][w]) {
                distanza[w] = distanza[u] + W[u][w];
                predecessori[w] = u;
                pq.push({-distanza[w], w}); //update priorità di w con nuova distanza
            }
        }
    }
    // Costruzione dell'albero dei cammini minimi
    unidirected_graph albero;
    for (int i : grafo.all_nodes()) {
        if (predecessori[i] != -1 && predecessori[i] != i) {
            albero.add_edge(predecessori[i], i);
        }
    }
    return albero;
};