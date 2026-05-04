#include "sort.hpp"
#include <iostream>
#include <vector>
#include <utility> 
#include "randfiller.h"



		

int main() {

	//testo stringhe
	std:: vector<std::string> stringa = {"ciao","hello","quando","will","mirtillo","dopo","come","tastiera","musica", "tg"};
	selection_sort(stringa);
	
	if (!is_sorted(stringa)) { 
		std::cerr << "Ordinamento fallito" << std::endl;
		return EXIT_FAILURE;
	}

	randfiller rf;
    std::vector<int> vdim ;
    vdim.resize(100);
    rf.fill(vdim,100,1000);
    
    for (int i=0; i <100; i++){
	    
	    std::vector<int> vi;
	    vi.resize(vdim[i]);
	    rf.fill(vi, -1000, 1000);
	    selection_sort(vi);
	    if (!is_sorted(vi)){
		    std::cerr<< "ordinamento fallito" << std::endl;
			return EXIT_FAILURE;
	    }

		std::vector<float> vf;
		vf.resize(vdim[i]);
		rf.fill(vf, -1000.0f, 1000.0f);
		selection_sort(vf);
		if (!is_sorted(vf)) {
			std::cerr << "Ordinamento fallito" << std::endl;
			return EXIT_FAILURE;
		}

		std::vector<double> vd;
		vd.resize(vdim[i]);
		rf.fill(vd, -1000.0, 1000.0);
		selection_sort(vd);
		if (!is_sorted(vd)) {
			std::cerr << "Ordinamento fallito" << std::endl;
			return EXIT_FAILURE;
		}
    }
    return EXIT_SUCCESS;
}