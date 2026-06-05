#include <vector>
#include <queue>
#include "graphs.hpp"
#include "contenitori.hpp" ////importare file
#include "graph_visit.hpp"

inline int prodotto_scalare(const std::vector<bool>& S, const std::vector<bool>& P) {
    int sum = 0;
    for (size_t i = 0; i < S.size(); ++i) {
        if (S[i] && P[i]) {
            sum++;
        }
    }
    return sum % 2; // return 0 o 1
}

inline std::vector<bool> differenza_simmetrica(const std::vector<bool>& Sj, const std::vector<bool>& Si) {
    std::vector<bool> risultato(Sj.size());
    for (size_t i = 0; i < Sj.size(); ++i) {
        risultato[i] = Sj[i] ^ Si[i]; // Operatore XOR
    }
    return risultato;
}

// Struttura per mappare gli archi originali
struct arco {
    int u, v;
    int peso;
};

// Funzione helper per generare il grafo ausiliario G' basato su S_i
// Restituisce una matrice di adiacenza (o una lista) per G' di dimensione 2V x 2V
unidirected_graph<int> build_lifting_graph(const unidirected_graph<int>& G, const std::vector<bool>& Si) {
    unidirected_graph<int> G_primo;
    auto archi = G.all_edges();
    int V = *G.all_nodes().rbegin() + 1; //offset per gli indici
 
    for (const auto& arco : archi) {
        int u   = arco.from();
        int v   = arco.to();
        double w = G.weight(u, v);
        int idx = G.edge_number(arco);
 
        if (Si[idx]) {
            // Archi incrociati: collegano le due "copie" opposte
            G_primo.add_edge(u, v + V, w);  // u+ → v-
            G_primo.add_edge(u + V, v, w);  // u- → v+
        } else {
            // Archi paralleli: collegano le due "copie" uguali
            G_primo.add_edge(u, v, w);  // u+ → v+
            G_primo.add_edge(u + V, v + V, w);  // u- → v-
        }
    }
    return G_primo;
}

std::vector<bool> find_minimal_cycle(const unidirected_graph<int>& G, const std::vector<bool>& Si) {
    auto nodi = G.all_nodes();
    auto archi = G.all_edges();
    int V= *nodi.rbegin() + 1; //offset per gli indici
    //int V_primo = 2 * V;
    int m = G.all_edges().size();
 
    unidirected_graph<int> G_primo = build_lifting_graph(G, Si);
    int INF= 1e9;
    std::vector<bool> ciclo_ottimo;
    double peso_minimo = INF;
 
    for (int v : G.all_nodes()) {
        int target = v + V; // v-
 
        unidirected_graph<int> albero = dijkstra(G_primo, v);
 
        // Ricostruiamo il cammino v → target con BFS sull'albero
        std::map<int, int> parent;
        std::queue<int> q;
        q.push(v);
        parent[v] = -1;

        bool trovato = false;
        while (!q.empty() && !trovato) {
            int cur = q.front(); q.pop();
            for (int nb : albero.neighbours(cur)) {
                if (parent.find(nb) == parent.end()) {
                    parent[nb] = cur;
                    if (nb == target) { 
                        trovato = true; 
                        break; 
                    }
                    q.push(nb);
                }
            }
        }
        if (!trovato) continue; 
                
        std::vector<int> path;
        for (int cur = target; cur != -1; cur = parent[cur])
            path.push_back(cur);
        std::reverse(path.begin(), path.end());
 
        // Calcola peso del cammino     
        double peso = 0;
        for (size_t i = 0; i + 1 < path.size(); ++i)
            peso += G_primo.weight(path[i], path[i + 1]);
 
        if (peso >= peso_minimo) continue;
 
        std::vector<bool> C_mu(m, false);
        for (size_t i = 0; i + 1 < path.size(); ++i) {
            int n1 = path[i] % V;  // nodo originale
            int n2 = path[i+1] % V;
            unidirected_edge<int> e(n1, n2);
            // Verifica che l'arco esista nel grafo originale
            auto all = G.all_edges();
            if (all.find(e) != all.end()) {
                int idx = G.edge_number(e);
                C_mu[idx] = C_mu[idx] ^ true; //inverte il valore del bool
            }
        }
 
        peso_minimo  = peso;
        ciclo_ottimo = C_mu;
    }
    return ciclo_ottimo;
}

// Funzione principale di De Pina
std::vector<std::vector<bool>> de_pina(const unidirected_graph<int>& G, int nodo_sorgente) {
    
    // 1. CALCOLO ALBERO E COALBERO (Usando le tue funzioni!)
    lifo<int> pila;
    unidirected_graph<int> T = graph_visit(G, nodo_sorgente, pila); // T = dfs(G)
    unidirected_graph<int> C = G - T;                               // C = G \ T
    
    int m = G.all_edges().size();
    int k = C.all_edges().size(); // Il numero di cicli è esattamente il numero di archi scartati
    
    // 2. INIZIALIZZAZIONE DEI VETTORI S_i
    std::vector<std::vector<bool>> S(k, std::vector<bool>(m, false));
    int l = 0;
    for (const auto& arco_coalbero : C.all_edges()) {
        int idx = G.edge_number(arco_coalbero);
        S[l][idx] = true; // Ogni S_l ha un solo '1' in corrispondenza del suo arco nel coalbero
        l++;
    }

    // 3. CICLO ALGEBRICO DI DE PINA (Esattamente l'Algorithm 2 delle note)
    std::vector<std::vector<bool>> B; // Base dei cicli minimi
    
    for (int i = 0; i < k; ++i) {
        // Trova il ciclo minimo (richiede il lifting e il tuo Dijkstra)
        std::vector<bool> Ci = find_minimal_cycle(G, S[i]);
        B.push_back(Ci); 

        // Aggiorna gli S_j successivi con lo XOR
        for (int j = i+1; j < k; j++) {
            if (prodotto_scalare(Ci, S[j]) == 1)
                S[j] = differenza_simmetrica(S[j], S[i]);
        }
    }

    return B;
}