#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <stdexcept>
#include "grafi.hpp"

int main(){

    unidirected_graph g;
    unidirected_graph g2;

	//creo il grafo
    g.add_edge(1, 2); 
    g.add_edge(3, 4); 
    g.add_edge(5,6);
    g.add_edge(4,6);
    g.add_edge(10,5);
    g.add_edge(2,10);
    g.add_edge(10,2); //provo ad aggiungere un duplicato
    
    std::cout<< "***** ALL_EDGES *****\n";
    std::cout<< "tutti gli archi:\n";
    std::set<unidirected_edge> archi = g.all_edges();
    for (const auto& arco : archi) {
        std::cout << arco << " "; 
    }
    std::cout << std::endl;
    
    
    std::cout<< "***** NEIGHBORS *****\n";
    int nodo=4; //in input
    std::cout<< "nodi vicini a "<< nodo <<": ";
    std::set<int> vicini = g.neighbors(nodo);
    for (const auto& nodo: vicini){
	    std::cout<< nodo << " ";
	} 
	std::cout<<std::endl;
	
	std::cout<< "***** ALL_NODES *****\n";
    std::cout<< "tutti i nodi: ";
    std::set<int> nodi = g.all_nodes();
    for (const auto& nodo : nodi) {
        std::cout << nodo << " "; 
    }
    std::cout << std::endl;
    
    //la posizione parte da indice=0 
 
	std::cout<< "***** EDGE_NUMBER *****\n";
	auto arco= unidirected_edge(5,10); //in input
    std::cout<< "l'arco "<< arco << " si trova in posizione: "<< g.edge_number(arco)<< "\n";

	std::cout<< "***** EDGE_AT *****\n";
	int posizione= 3; //in input
    std::cout<< "in posizione "<< posizione << " c'è l'arco: "<< g.edge_at(posizione)<< "\n";
    
    g2.add_edge(3,4);
    g2.add_edge(6,4);

    unidirected_graph diff = g - g2;

	std::cout<< "***** OPERATORE '-' *****\n";
    auto archi_diff = diff.all_edges();
    std::cout << "differenza G - G2: "<< "\n";
    for (const auto& arco : archi_diff) {
        std::cout << arco << " ";  
    }
    std::cout << std::endl;
    
    return 0;
}