#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>


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

//merge 
template <typename T>
void merge(std::vector <T>& vec, int p, int q, int r)
{
    if (vec.size() <2) {
        return;
    }
    int n1= q-p+1;
    int n2= r-q;
    std::vector<T> L(n1), R(n2);
    for (int i=0; i< n1; i++){
        L[i]= vec[p+i];
    } 
    for (int j=0; j< n2; j++){
        R[j]=vec[q+j+1];
    }
    int i=0;
    int j=0;
    int k=p;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } 
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }
    //Se avanzano elementi in L
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }
    //Se avanzano elementi in R 
    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
    return;
}

//merge sort
template<typename T>
void merge_sort(std::vector <T>& vec, int p, int r){
    if (p<r){
        int q= std::floor(p+r)/2;
        merge_sort(vec, p, q);
        merge_sort(vec, q+1, r);
        merge(vec, p, q, r);
    }
}

//partition
template<typename T>
int partition(std::vector <T>& vec, int p, int r){
    T x= vec[r];
    int i=p-1;
    for (int j=p; j<r; j++){
        if (vec[j]<= x){
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i+1], vec[r]);
    int q= i+1;
    return q;
}


//quicksort sort
template<typename T>
void quick_sort(std::vector <T>& vec, int p, int r){
    if (p<r){
        int q= partition(vec, p, r);
        quick_sort(vec, p, q-1);
        quick_sort(vec, q+1, r);
    }
}

//
//quicksort versione veloce per n piccoli

//insertion sort che ordina solo da un indice p a un r

template<typename T>
void insertionsort_veloce(std::vector <T>& vec, int p, int r) {
    for (int i = p + 1; i <= r; i++) {
        T value = vec[i];
        int j = i-1;
        while (j >= p && vec[j] > value) {
            vec[j + 1] = vec[j];
            j=j-1;
        }
        vec[j + 1] = value;
    }
}

//insertion e quick sort insieme
template <typename T>
void quicksort_veloce(std::vector<T>& vec, int p, int r, int soglia) {
    // Calcoliamo la dimensione della fetta attuale
    int size = r - p + 1;

    if (size <= soglia) {
        insertionsort_veloce(vec, p, r);
    } 
    if (p < r) {
        int q = partition(vec, p, r);
        quicksort_veloce(vec, p, q - 1, soglia);
        quicksort_veloce(vec, q + 1, r, soglia);
    }
}
