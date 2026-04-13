#include <algorithm>
#include <iostream>
#include <vector>


//funzione is_sorted
template <typename T>
bool is_sorted(const std::vector <T>& vec){
    if (vec.size() < 2) { //se il vettore è vuoto (o ha un solo elem) allora è ordinato
        return true;
    }
    for (int i=0; i<vec.size()-1; i++){
        if (vec[i+1]<vec[i]){
            return false;
        }
    }
    return true;
}


//bubble sort
template <typename T>
void bubble_sort(std::vector <T>& vec)
{
    if (vec.size() <2) {
        return;
    }
    int n=vec.size();
    for (int i=0; i < n-1; i++) {
        for (int j=n-1; j>i; j--){
            if (vec[j]< vec[j-1]){
                std::swap (vec[j], vec[j-1]);
            }
        }
    }
    return;
}

//insertion sort
template <typename T>
void insertion_sort(std::vector <T>& vec)
{
    if (vec.size() <2) {
        return;
    }
    int n=vec.size();
    for (int i=1; i < n; i++) {
        T value = vec[i];
        int j = i-1;
        while ( j>=0 && vec[j]> value){
                vec[j+1] = vec[j] ;
                j = j-1 ;
            }
        vec[j+1] = value;
    }
    return;
}

//selection sort
template <typename T>
void selection_sort (std::vector <T>& vec)
{
    if (vec.size() <2) {
        return;
    }
    int n= vec.size();
    for (int i=0; i < n-1 ; i++) {
        int min_index =i;
        for (int j=i+1; j<n; j++) {
            if (vec[j]< vec[min_index]){
                min_index=j;
            }
        }
        if (min_index != i){
            std::swap (vec[i], vec[min_index]);
        }
    }
    return;
}
