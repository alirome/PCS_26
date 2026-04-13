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

    for (int size=4; size<= 8192; size*=2){
        std::vector<int> vec(size);
        rf.fill (vec, -1000, 1000);
        
        std::cout << "=========size: "<< size << "==========" <<'\n';

        //bubble
        std::vector<int> v_bubble = vec;
        tc.tic();
        bubble_sort(v_bubble);
        double secs_bubble = tc.toc();
        
        std::cout << "bubble sort time:    "<< secs_bubble << " secs\n";

        //insertion
        std::vector<int> v_insertion = vec;
        tc.tic();
        insertion_sort(v_insertion);
        double secs_insertion = tc.toc();
        
        std::cout << "insertion sort time: "<< secs_insertion << " secs\n";

        //selection
        std::vector<int> v_selection = vec;
        tc.tic();
        selection_sort(v_selection);
        double secs_selection = tc.toc();
        
        std::cout << "selection sort time: "<< secs_selection << " secs\n";

        //sort()
        std::vector<int> v_sort = vec;
        tc.tic();
        std::sort(v_sort.begin(), v_sort.end());
        double secs_sort = tc.toc();
        
        std::cout << "sort time:           "<< secs_sort << " secs\n";
    }
    
    return EXIT_SUCCESS;
}

