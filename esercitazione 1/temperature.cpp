#include <fstream>
//#include <string>
#include <iostream>
using namespace std;

int main(void){
    std::cout << "Enter file name: \n";
    std::string filename;
    std::cin >> filename;
    std::ifstream ifs(filename);
    if ( ifs.is_open() ) { 
        std::string location;
        double temp1, temp2, temp3, temp4;
        double average;
        for (int r=0; r<=2; r++){
            ifs >> location >> temp1 >> temp2 >> temp3 >> temp4 ;
            average= (temp1+temp2+temp3+temp4)/4;
            std::cout << location << ' ' << average << '\n';
        }
        ifs.close(); 
    }
    else {
        std::cerr << "errore: file non trovato";
    }
    return 0;
}