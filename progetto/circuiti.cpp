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
    
    //stampa cicli
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
    }

    //creare vettore resistori e struttura componenti
    std::vector<struttura> resistenze;
    for (const auto& coppia : C.componenti) {
        if (coppia.second.type.front() == 'R') {   //confronta il primo carattere
            resistenze.push_back(coppia.second);
        }
    }
    std::vector<struttura> generatori;
    for (const auto& pair : C.componenti) {
        if (pair.second.type.front() == 'V') {
            generatori.push_back(pair.second);
        }
    }

    //creo matrice di incidenza e resistenza
    //n= numero di cicli 
    //m= numero di resitori
    Eigen::MatrixXd R= costruzione_R (resistenze); //resistenza mxm
    Eigen::MatrixXd B= costruzione_B (resistenze , cicli ); //incidenza mxn
    Eigen::VectorXd v = costruzione_v (generatori, cicli);
    

    std::cout << "Numero di resistenze trovate, m= " << resistenze.size() << "\n";
    std::cout << "Numero di maglie (cicli) trovate, n=" << cicli.size() << "\n";
    std::cout << "Matrice R (Diagonale delle Resistenze):\n" << R << "\n\n";
    std::cout << "Matrice B (Incidenza Maglie-Resistenze):\n" << B << "\n\n";
    std::cout << "Vettore dei termini noti (v):\n" << v << "\n\n";

    return 0;
}