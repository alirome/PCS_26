#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include "contenitori.hpp"
#include "graphs.hpp"

template <typename T, typename contenitore>
unidirected_graph<T> graph_visit2(const unidirected_graph<T> g, const T& nodo_s, contenitore& c)  //prendo un grafo, il nodo sorgente e un contenitore(pila o coda, a seconda che voglia usare BFS o DFS)
{
	unidirected_graph<T> albero;
	std::set<T> visitati;   //sostituisce il ciclo for che controlla azzera tutte le posizioni
	
	c.put(nodo_s);
	visitati.insert(nodo_s);
	
	//BFS e DFS hanno struttura identica, colo che uno usa la pila uno usa la coda. creando un contenitore e le funzioni in contenitori.hpp che hanno nomi uguali per i due tipi di contenitore, posso scegliere in seguito quale usare
	while(!c.empty())
	{
		T z=c.get();
		for (const T& w : g.neighbours(z))
		{
			if(visitati.find(w) == visitati.end())  // se non trova in nodo w nel set di nodi già visitati
			{
				visitati.insert(w);  //inserisco w nei nodi visitati
				double peso = g.weight(z, w);
				albero.add_edge(z,w,peso);  //aggiungo il ramo all'albero
				c.put(w);             
			}
		}
	}
	return albero;
	
}

template <typename T>
bool findpath(const unidirected_graph<T>& albero, const T& u, const T& v, std::set<T>& visited, std::vector<T>& path)
{
    visited.insert(u);
    path.push_back(u);  //aggiunge il nodo che sto esplorando
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
    path.pop_back();  //se questa strada non porta a v, rimuovo il nodo che sto esplorando
    return false;
}

template <typename T>
struct struttura_cicli{
    std::vector<T> nodes;                           // lista ordinata dei nodi del ciclo (es: 1->2->3->1)
    std::set<unidirected_edge<T>> edges;            // set degli archi che compongono il ciclo
};

template <typename T>
std::vector<struttura_cicli<T> > cicli_fondamentali_dfs(const unidirected_graph<T>& grafo, const T& nodo_sorgente)
{
    lifo<T> stack;
    unidirected_graph<T> A = graph_visit2(grafo, nodo_sorgente, stack);  //albero dfs usando lo stack
    unidirected_graph<T> coalbero = grafo - A;    // coalbero C=G\T  (archi in G ma non in T)
    std::vector<struttura_cicli<T>> cicli;        

    for (const unidirected_edge<T>& arco : coalbero.all_edges())   //per ogni arco (u,v) in C trova il percorso da u a v in T, il quale unito all'arco (u,v) forma un ciclo fondamentale
    {
        T u = arco.from();
        T v = arco.to();

        std::set<T> visited;
        std::vector<T> path; 
        if (findpath(A, u, v, visited, path))
        {
            struttura_cicli<T> ciclo;
            ciclo.nodes = path;   // path contiene (u,v)
            ciclo.nodes.push_back(u);
            auto it = std::min_element(ciclo.nodes.begin(), ciclo.nodes.end() - 1); // -1 per escludere l'ultimo nodo (che è uguale al primo)
            std::rotate(ciclo.nodes.begin(), it, ciclo.nodes.end() - 1);
            ciclo.nodes.back() = ciclo.nodes.front();  // aggiorna il nodo di chiusura

            for (size_t i = 0; i + 1 < ciclo.nodes.size(); ++i)
            {
                ciclo.edges.insert(unidirected_edge<T>(ciclo.nodes[i], ciclo.nodes[i+1]));   //set degli archi nel ciclo
            }
			
            //ciclo.edges.insert(unidirected_edge<T>(u,v));       // Arco di chiusura dal coalbero (v,u)
            
            cicli.push_back(ciclo);
        }
    }
    return cicli;
}