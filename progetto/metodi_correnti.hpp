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

unidirected_graph<T> lettura(const string& nome){
    unidirected_graph<T> G;
    ifstream ifs(nome);
    if ( ifs.is_open() ){
        while ( !ifs.eof() ){
            string tipo;
            double peso;
            int nodo1, nodo2;
            G.add_edge(nodo1, nodo2, peso); //il peso è double
        }
    }
    else {
        std::cerr << "ERRORE: il file non è stato aperto correttamente"<< std::endl ; 
        //return 1; serve?
    }

}