#include <iostream>
#include <algorithm>
#include "sort.hpp"
#include <vector>
#include "randfiller.h"
#include <chrono>
#include <thread>
#include "timecounter.h"


int main(void) {
	timecounter tc;
	randfiller rf;
    int soglia=0;
    int n_vett= 100;
    for (int size=2; size<= 100; size=size+2){
        
        std::vector<std::vector<int>> vettori(n_vett, std::vector<int>(size));
        
        for (int i = 0; i < n_vett; i++) {
            rf.fill(vettori[i], -10000, 10000);
        }        

        std::cout << "=========size: "<< size << "==========" <<'\n';

        //bubble
        std::vector<std::vector<int>> v_bubble = vettori;
        tc.tic();
        for (int i=0; i < n_vett; i++){
            bubble_sort(v_bubble[i]);
        }
        double secs_bubble = tc.toc() /n_vett;
        std::cout << "bubble sort time:    "<< secs_bubble << " secs\n";

        //insertion
        std::vector<std::vector<int>> v_insertion = vettori;
        tc.tic();
        for (int i=0; i < n_vett; i++){
            insertion_sort(v_insertion[i]);
        }
        double secs_insertion = tc.toc() /n_vett;
        
        std::cout << "insertion sort time: "<< secs_insertion << " secs\n";

        //selection
        std::vector<std::vector<int>> v_selection = vettori;
        tc.tic();
        for (int i=0; i < n_vett; i++){
            selection_sort(v_selection[i]);
        }
        double secs_selection = tc.toc() /n_vett;
        
        std::cout << "selection sort time: "<< secs_selection << " secs\n";

        //sort()
        std::vector<std::vector<int>> v_sort = vettori;
        tc.tic();
        for (int i=0; i < n_vett; i++){
            std::sort(v_sort[i].begin(), v_sort[i].end());
        }
        double secs_sort = tc.toc() /n_vett;
        
        std::cout << "sort time:           "<< secs_sort << " secs\n";
    
        //merge
        std::vector<std::vector<int>> v_merge = vettori;
        tc.tic();
        int p=0;
        for (int i=0; i < n_vett; i++){
            int r= v_merge[i].size()-1;
            merge_sort(v_merge[i], p, r);
        }
        double secs_merge = tc.toc() /n_vett;
        
        std::cout << "merge sort time:     "<< secs_merge << " secs\n";
    
        //quicksort
        std::vector<std::vector<int>> v_quick = vettori;
        tc.tic();
        int p1=0; 
        for (int i=0; i < n_vett; i++){
            int r1=v_quick[i].size()-1;
            quick_sort(v_quick[i], p1, r1);
        }
        double secs_quick = tc.toc() /n_vett;
        
        std::cout << "quick sort time:     "<< secs_quick << " secs\n";
        
        if (secs_insertion<secs_quick) {
            soglia= size; 
        }

        //quick sort veloce con insertion sort sotto la soglia
        std::vector<std::vector<int>> v_ibrido = vettori;
        tc.tic();
        int p2=0; 
        for (int i=0; i < n_vett; i++){
            int r2=v_ibrido[i].size()-1;
            quicksort_veloce(v_ibrido[i], p2, r2, soglia);
        }
        double secs_ibrido = tc.toc() /n_vett;
        
        std::cout << "ibrido sort time:   "<< secs_ibrido << " secs\n";

    }
    std::cout<< "Al di sotto della soglia "<< soglia << " i metodi quadratici sono più veloci di quelli logaritmici" << "\n";


    return EXIT_SUCCESS;
}

