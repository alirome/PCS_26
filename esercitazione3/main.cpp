#include <iostream>
#include "es3.hpp"
#include <numeric>
#include <concepts>
#include <sstream>

int main(void){

    std::cout << "prima frazione- \ninserire numeratore e denominatore: " ;
    int n1;
    int d1;
    std::cin >> n1>> d1; 
    rational<int> a(n1, d1);

    std::cout << "seconda frazione- \ninserire numeratore e denominatore: " ;
    int n2;
    int d2;
    std::cin >> n2 >>d2; 
    rational<int> b(n2, d2);

    //stampa frazioni
    std::cout << "prima frazione:   " << a << '\n';
    std::cout << "seconda frazione: " << b << '\n';
    
    //somma
    rational<int> somma = a+b;
    std::cout << "somma:      " << somma << '\n';

    //differenza
    rational<int> diff = a-b;
    std::cout << "differenza: " << diff << '\n';

    //prodotto
    rational<int> prod = a*b;
    std::cout << "prodotto:   " << prod << '\n';

    //divisione
    rational<int> quoz = a/b;
    std::cout << "quoziente:  " << quoz << '\n';


    return 0;

}
