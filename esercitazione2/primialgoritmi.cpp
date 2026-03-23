#include <iostream>
#include <algorithm>
#include <string_view>
#include <cmath>
#include <initializer_list>

//template <typename T>
//T get_min(std::initializer_list<T> ilist)
//{
    //return *std::min_element(ilist.begin(), ilist.end());
//}


int main()
{
    static const int N = 10;
    double arr[N]= {11, 20, 4, 22, 2, 5.5, 7, 8.9, 9, 0.5};
    
    double min_val= arr[0];
    double max_val= arr[0];
    double somma= 0;
    
    for (int i = 0; i < N; ++i) {
        min_val = std::min(min_val, arr[i]);
        max_val = std::max(max_val, arr[i]);
        somma += arr[i];
    }

    double sommascarti= 0;
    double media= somma/N;
    //formula deviazione standard: sqrt( Σ(arr[i] - media)^2 / N )
    for (int j = 0; j < N; ++j){
        sommascarti += (arr[j]- media)*(arr[j]- media);
    }
    double deviazione_standard= std::sqrt(sommascarti/N);

    std::cout << "minimo: " << min_val << '\n';
    std::cout << "massimo: " << max_val << '\n';
    std::cout << "deviazione standard: " << deviazione_standard << '\n';
    
    //double m = get_min(std::initializer_list<double> {11, 20, 4, 22, 2, 5.5, 7, 8.9, 9, 0.5} );
    
    return 0;
}