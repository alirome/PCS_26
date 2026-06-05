#pragma once
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include "graphs.hpp"
#include "cicli_fondamentali.hpp"
#include "DePina.hpp"

//usiamo add_edge per creare gli archi delle resistenze e generatori come mappa di vettore (nodo,nodo) e peso (valore della resistenza/del generatore)
//POSSIBILI DOMANDE ALL'ESAME?
//perchè usiamo una mappa? cosa comporta? c'è un modo più semplice? 
//aggiungiamo un campo agli archi con un label R/V

struct struttura {
    std::string type;    // 'R' o 'V'
    double value;
    int sign;     // +1 se nodo1 < nodo2 nella netlist, -1 altrimenti
    int nodo1;
    int nodo2;
};

struct circuito{
    unidirected_graph<int> G;
    std::map<unidirected_edge<int>, struttura> componenti;
};

circuito lettura(const std::string& nome){
    unidirected_graph<int> G;
    std::map<unidirected_edge<int>, struttura> componenti;
    std::ifstream ifs(nome);
    circuito c;

    if ( ifs.is_open() ){
        std::string tipo;
        double peso;
        int nodo1, nodo2;
        
        while ( ifs >> tipo>> peso >> nodo1 >> nodo2 ){

            //gestisco gli errori
            if (nodo1==nodo2){
                std::cerr << "ERRORE: l'arco è un loop" << std::endl ;
                continue;
            }


            unidirected_edge<int> nuovo_arco(nodo1, nodo2);
            auto archi_attuali =c.G.all_edges();

            if (archi_attuali.find(nuovo_arco) != archi_attuali.end()){
                std::cerr<< "ERRORE: l'arco esiste già" << std::endl ; //controllare 
                continue;
            }
                
            c.G.add_edge(nodo1, nodo2, peso); //il peso è double

            if (nuovo_arco.from()== nodo1) { //se il nodo1 è il minore prendo il segno positivo
                c.componenti[nuovo_arco] = struttura{ tipo, peso, +1, nodo1, nodo2};
            } 
            else {
                c.componenti[nuovo_arco] = struttura{ tipo, peso, -1, nodo1, nodo2 };
            }
        }
    }
    else {
        std::cerr << "ERRORE: il file non è stato aperto correttamente"<< std::endl ; 
        return c;
    }
    return c;
}

