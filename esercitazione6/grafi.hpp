#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <stdexcept>

//il programma utilizza map e set, nonostante siano meno efficient di unordered_map, per leggibilità del programma. 
//In particolare set per memorizzare gli archi del grafo e map per creare la lista di adiacenza dei nodi.

class unidirected_edge {
private:
    int nodo_a;
    int nodo_b;

public:
    // Il costruttore garantisce che node_a < node_b
    unidirected_edge(int u, int v) {
        nodo_a = std::min(u, v);
        nodo_b = std::max(u, v);
    }

    int from() const { 
        return nodo_a;
    }
    int to() const { 
        return nodo_b; 
    }

    // Operatore di uguaglianza
    bool operator==(const unidirected_edge& other) const {
        return (nodo_a == other.nodo_a && nodo_b == other.nodo_b);
    }

    // Operatore minore 
    bool operator<(const unidirected_edge& other) const {
        if (nodo_a != other.nodo_a) {
            return nodo_a < other.nodo_a;
        }
        return nodo_b < other.nodo_b;
    }

    // Operatore di output
    //friend stampa un oggetto personalizzato
    friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& edge) {
        os << "(" << edge.nodo_a << " -- " << edge.nodo_b << ")";
        return os;
    }
};

class unidirected_graph{
private:
    std::set <unidirected_edge> archi;             
    std::map < int, std::set<int> > lista_adiacenza;  //chiave: nodo, valori:lista di nodi adiacenti
public:
    unidirected_graph() = default;
    unidirected_graph(const unidirected_graph& other) = default;
    
    //neighbors
    std::set<int> neighbors(int nodo) const {
        if (lista_adiacenza.count(nodo)) {
            return lista_adiacenza.at(nodo);
        }
        return {}; // Restituisce un set vuoto se il nodo non ha vicini 
    }

    //add edge() che permetta di aggiungere un arco al grafo
    void add_edge(int u, int v){
        if (u==v) {
            return;
        }
        unidirected_edge new_edge(u, v);
        archi.insert(new_edge);
        lista_adiacenza[u].insert(v);
        lista_adiacenza[v].insert(u);
    }

    // all edges() che restituisce tutti gli archi
    std::set<unidirected_edge> all_edges() const {
        return archi; 
    }

    // all nodes() che restituisce tutti gli nodi
    std::set<int> all_nodes() const {
        std::set<int> nodi; //lista di nodi
        
        for (const auto& pair : lista_adiacenza) {
            // pair.first è la chiave della mappa
            nodi.insert(pair.first);
        }
        
        return nodi;
    }
    
    //  edge number() che, dato un arco (e), ne restituisce la sua numerazione all’interno del grafo
    int edge_number(const unidirected_edge& e) const {
        //std::set<unidirected_edge>::const_iterator 
        auto edge1 = archi.find(e);
    
        // Se non lo trova, eccezione
        if (edge1 == archi.end()) {
            throw std::out_of_range("Arco non presente nel grafo");
        }
        return std::distance(archi.begin(), edge1);
    }

    //  edge at() che, dato un numero d’arco (p), restituisce il corrispondente oggetto arco all’interno del grafo,
    unidirected_edge edge_at(int p) const{
        if (p>= archi.size()){
            throw std::out_of_range("Indice arco fuori dai limiti"); //gestisco eccezione
        }
        auto arco = std::next(archi.begin(), p); //prende l'elemento in posizione p
    
        return *arco; //referenziato
    }

    // operator-(): che permette di calcolare la differenza tra due grafi
    unidirected_graph operator-(const unidirected_graph& other) const{
        unidirected_graph result;
        for (const auto& edge : this->archi) {
            
            if (other.archi.find(edge) == other.archi.end()) {
                result.add_edge(edge.from(), edge.to());
            } 
        }
        return result;
    }

};