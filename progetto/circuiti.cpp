#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "metodi_correnti.hpp"
#include "graphs.hpp"


int main(){
    circuito C=lettura("../netlist.txt"); //la netlist non si trova in build/
    unidirected_graph<int>& G=C.G;
    for (const auto& arco : G.all_edges()){
        std::cout<< arco.from()<< "---" << arco.to() << "\n";
    }
    
    unidirected_edge<int> arco_sorgente= G.edge_at(0);
    std::vector<struttura_cicli<int>> cicli = cicli_fondamentali_dfs(G, arco_sorgente.from());
    
    int n= 0;

    for (size_t i = 0; i < cicli.size(); ++i) {
        std::cout << "\nCiclo " << i << ":" << std::endl;
        std::cout << "Nodi nel path: ";
        for (int g : cicli[i].nodes)
            std::cout << g << " ";
        std::cout << std::endl;
        std::cout << "Archi: ";
        for (const auto& e : cicli[i].edges)
            std::cout << e << " ";
        std::cout<< "\n";
        std::cout<< "ciclo "<< i+1<< " : ";
        for (size_t j=0; j< cicli[i].nodes.size(); ++j){
            std::cout<< cicli[i].nodes[j];
            if ( j+1 < cicli[i].nodes.size())
                std::cout<< " -> ";
        }
        std::cout<< "\n";
        std::cout << std::endl;
        n= i;
    }

    int m=0;
    //for (const auto& arco : G.all_edges()){
        //if (arco.tipo == 'R'){
            //m=m+1;
        //}
    //}

    //creo matrice di incidenza e resistenza
    //n= numero di cicli //parte da 0
    //m= numero di resitori
    Eigen::MatrixXd R; //resistenza
    Eigen::MatrixXd B; //incidenza



    return 0;
}