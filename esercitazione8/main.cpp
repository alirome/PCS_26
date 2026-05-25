#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

int main() {
    unsigned int n = 3;
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);

    const double tol=1.0e-15;
    if (abs(B.determinant())<tol)
        return -1;

    // matrice simmetrica e definita positiva
    Eigen::MatrixXd A = B.transpose() * B; 
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    Eigen::VectorXd b = A * x_ex;

    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n);
    const double res_tol =1.0e-12;
    const unsigned int it_max= 10000;
    auto [it, x] = gradiente_coniugato(A, b, x0, tol, it_max);

    auto err_relativo= (x_ex.norm()==0.0)? (x-x_ex).norm(): (x-x_ex).norm()/x_ex.norm();
    std::cout << "Condizionamento matrice:\n" << condA(A) << std::endl;

    std::cout.precision(4);
    std::cout << "numero iterazioni:\n" << it << std::endl;
    std::cout << "Soluzione esatta:\n" << x_ex << std::endl;
    std::cout << "Soluzione calcolata:\n" << x << std::endl;
    std::cout << "Errore relativo: " << (x - x_ex).norm() / x_ex.norm() << std::endl;

    
    return 0;
}