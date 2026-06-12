#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include "contenitori.hpp"
#include "graphs.hpp"

// Visita generica (BFS o DFS a seconda del contenitore passato)
template <typename T, typename contenitore>
unidirected_graph<T> graph_visit2(const unidirected_graph<T> g, const T& nodo_s, contenitore& c)
{
    unidirected_graph<T> albero;
    std::set<T> visitati;

    c.put(nodo_s);
    visitati.insert(nodo_s);

    while (!c.empty())
    {
        T z = c.get();
        for (const T& w : g.neighbours(z))
        {
            if (visitati.find(w) == visitati.end())
            {
                visitati.insert(w);
                double peso = g.weight(z, w);
                albero.add_edge(z, w, peso);
                c.put(w);
            }
        }
    }
    return albero;
}

template <typename T>
struct struttura_cicli {
    std::vector<T> nodes;            // nodi del ciclo, primo == ultimo  (es: 1->2->3->1)
    std::set<unidirected_edge<T>> edges;   // archi che compongono il ciclo
};

// ---------------------------------------------------------------------------
// Ricerca del percorso tra u e v nell'albero tramite DFS ricorsiva.
// Restituisce true e riempie 'path' con i nodi da u a v (u incluso, v incluso).
// ---------------------------------------------------------------------------
template <typename T>
bool findpath(const unidirected_graph<T>& albero,
              const T& u, const T& v,
              std::set<T>& visited,
              std::vector<T>& path)
{
    visited.insert(u);
    path.push_back(u);
    if (u == v)
        return true;
    for (const T& n : albero.neighbours(u))
    {
        if (visited.find(n) == visited.end())
        {
            if (findpath(albero, n, v, visited, path))
                return true;
        }
    }
    path.pop_back();
    return false;
}

// ---------------------------------------------------------------------------
// Ruota il vettore 'nodes' (che ha primo == ultimo) in modo che parta
// dal nodo minimo del ciclo.
// Esempio: {2,1,3,2} -> {1,3,2,1}
// ---------------------------------------------------------------------------
template <typename T>
void ruota_dal_minimo(std::vector<T>& nodes)
{
    if (nodes.size() < 2) return;

    // Cerca il nodo minimo escludendo l'ultimo (che è uguale al primo)
    auto it_min = std::min_element(nodes.begin(), nodes.end() - 1);

    // Ruota la parte [begin, end-1) in modo che it_min sia il nuovo inizio
    std::rotate(nodes.begin(), it_min, nodes.end() - 1);

    // Aggiorna il nodo di chiusura (ultimo) per farlo coincidere col nuovo primo
    nodes.back() = nodes.front();
}

// ---------------------------------------------------------------------------
// Cicli fondamentali tramite DFS.
// Per ogni arco del coalbero (G \ albero_DFS) trova il percorso nell'albero
// che, chiuso dall'arco stesso, forma un ciclo fondamentale.
// I cicli vengono normalizzati in modo da partire sempre dal nodo minimo.
// ---------------------------------------------------------------------------
template <typename T>
std::vector<struttura_cicli<T>> cicli_fondamentali_dfs(const unidirected_graph<T>& grafo,
                                                        const T& nodo_sorgente)
{
    // 1. Costruisci l'albero DFS
    lifo<T> stack;
    unidirected_graph<T> A = graph_visit2(grafo, nodo_sorgente, stack);

    // 2. Coalbero = archi in G ma non in T
    unidirected_graph<T> coalbero = grafo - A;

    std::vector<struttura_cicli<T>> cicli;

    // 3. Per ogni arco del coalbero costruisci un ciclo fondamentale
    for (const unidirected_edge<T>& arco : coalbero.all_edges())
    {
        T u = arco.from();   // nodo minore per costruzione di unidirected_edge
        T v = arco.to();

        // Trova il percorso u -> v nell'albero
        std::set<T> visited;
        std::vector<T> path;
        if (!findpath(A, u, v, visited, path))
            continue;   // non dovrebbe mai accadere in un grafo connesso

        struttura_cicli<T> ciclo;
        ciclo.nodes = path;          // es: [2, 1, 3]
        ciclo.nodes.push_back(u);    // chiudi il ciclo: [2, 1, 3, 2]

        // 4. Normalizza: fai partire il ciclo dal nodo minimo
        ruota_dal_minimo(ciclo.nodes);   // es: [1, 3, 2, 1]

        // 5. Costruisci il set degli archi del ciclo
        for (size_t i = 0; i + 1 < ciclo.nodes.size(); ++i)
            ciclo.edges.insert(unidirected_edge<T>(ciclo.nodes[i], ciclo.nodes[i + 1]));

        cicli.push_back(ciclo);
    }
    return cicli;
}
