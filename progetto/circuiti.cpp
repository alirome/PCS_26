#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "metodi_correnti.hpp"
#include "graphs.hpp"


int main(){
    circuito C=lettura("../netlist.txt"); //la netlist non si trova in build/
    
    unidirected_graph<int>& G=C.G;
    unidirected_edge<int> arco_sorgente= G.edge_at(0);
    std::vector<struttura_cicli<int>> cicli = cicli_fondamentali_dfs(G, arco_sorgente.from());
    std::vector<struttura_cicli<int>> maglie = de_pina_from_scratch( G, arco_sorgente.from()); 
    
    //stampa maglie
    for (size_t i = 0; i < maglie.size(); ++i) {
        std::cout << "maglia " << i+1 << ": ";
        for (size_t j=0; j< maglie[i].nodes.size(); ++j){
            std::cout<< maglie[i].nodes[j];
            if ( j+1 < maglie[i].nodes.size())
                std::cout<< " -> ";
        }
        std::cout<< "\n";
        std::cout << std::endl;
    }


    //stampa cicli
    for (size_t i = 0; i < cicli.size(); ++i) {
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
    Eigen::MatrixXd R = costruzione_R (resistenze); //resistenza mxm
    Eigen::MatrixXd B = costruzione_B (resistenze , cicli ); //incidenza mxn
    Eigen::MatrixXd B2 = costruzione_B (resistenze , maglie );
    Eigen::VectorXd v = costruzione_v (generatori, cicli); //vettore termini noti
    Eigen::VectorXd v2 = costruzione_v (generatori, maglie);
    Eigen::MatrixXd A = B.transpose() * R * B;
    Eigen::MatrixXd A2 = B2.transpose() * R * B2;
    Eigen::VectorXd i = A.colPivHouseholderQr().solve(v); 
    Eigen::VectorXd i2 = A2.colPivHouseholderQr().solve(v2);
    Eigen::VectorXd tensioni = R * B * i;
    Eigen::VectorXd correnti = B * i;
    Eigen::VectorXd tensioni2 = R * B2 * i2;
    Eigen::VectorXd correnti2 = B2 * i2;


    std::cout << "Matrice R (Diagonale delle Resistenze):\n" << R << "\n\n";
    std::cout << "Matrice B (Incidenza Maglie-Resistenze):\n" << B << "\n\n";
    std::cout << "matrice B2\n" << B2 << "\n\n";
    std::cout << "Vettore dei termini noti (v):\n" << v << "\n\n";
    std::cout << "vettori\n" << v2 << "\n\n";
    std::cout << "Vettore delle correnti di maglia (i):\n" << i << "\n\n";
    std::cout << "=! correnti\n" << i2 << "\n\n";

    for (int r=0; r<resistenze.size(); r++){
        std::cout << resistenze[r].type << ": V = " << tensioni[r] << " volts, I = " << correnti[r] << " amps.\n";
    }

    return 0;
}