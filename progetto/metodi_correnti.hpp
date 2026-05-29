#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "graphs.hpp"

//usiamo add_edge per creare gli archi delle resistenze e generatori come mappa di vettore (nodo,nodo) e peso (valore della resistenza/del generatore)
//POSSIBILI DOMANDE ALL'ESAME?
//perchè usiamo una mappa? cosa comporta? c'è un modo più semplice? 
//aggiungiamo un campo agli archi con un label R/V

struct struttura {
    char type;    // 'R' o 'V'
    double value;
    int sign;     // +1 se nodo1 < nodo2 nella netlist, -1 altrimenti
};

unidirected_graph<T> lettura(const string& nome){
    unidirected_graph<T> G;
    std::map<unidirected_edge<int>, struttura> componenti;
    ifstream ifs(nome);
    
    if ( ifs.is_open() ){
        while ( !ifs.eof() ){
            //std::replace ()
            string tipo;
            double peso;
            int nodo1, nodo2;

            //gestisco gli errori
            if (nodo1==nodo2){
                std::cerr << "ERRORE: l'arco è un loop" << std::endl ;
                return -1;
            }

            else {
                G.add_edge(nodo1, nodo2, peso); //il peso è double
                unidirected_edge<int> arco(nodo1, nodo2);

                for (const auto& arch: G.all_edges()){ //controllo se esiste già l'arco nel grafo
                    if (arco(nodo1, nodo2)== arch){
                        std::cerr<< "ERRORE: l'arco esiste già" << std::endl ;
                        return -1;
                    }
                }

                if (arco(nodo1, nodo2).from()== nodo1) { //se il nodo1 è il minore prendo il segno positivo
                    componenti[unidirected_edge<int> ( nodo1, nodo2 ) ] = { tipo, peso, +1 };
                } 
                else {
                    componenti[unidirected_edge<int> ( nodo1, nodo2 ) ] = { tipo, peso, -1 };
                }
            }
        }
    }
    else {
        std::cerr << "ERRORE: il file non è stato aperto correttamente"<< std::endl ; 
        //return 1; serve?
    }

}