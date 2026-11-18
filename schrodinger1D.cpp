#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <fstream>
#include <cmath>
#include <matplot/matplot.h>

using Eigen::MatrixXd;
using namespace matplot;

std::ofstream outfile("output.txt");

const double hbar = 1, m = 1, omega = 1;
double V(double x){ 
    return m * omega * omega * x * x / 2;
}

MatrixXd buildHamiltonian(int N){
    // H = -hbar^2 / 2m (d/dx)^2 + V(x)
    const double xmax = 10, xmin = -10, dx = ((xmax-xmin) / (N-1));
    double a = (-1 * hbar * hbar) / (2*m*dx*dx);
    Eigen::MatrixXd H(N, N);
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            double x = (xmin + dx * i);
            if(i==j){
                H(i,j) = V(x) - (2*a);
            }
            else if(i==j+1||i==j-1){    
                H(i,j) = a;
            }
            else{
                H(i,j) = 0;
            }
        }
    }
    //std::cout << H << std::endl;
    return H;
}

Eigen::VectorXd getEigen(int N){
        outfile << std::endl << "N=" << N << std::endl;

        Eigen::MatrixXd H = buildHamiltonian(N);
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(H);
        if (eigensolver.info() != Eigen::Success) abort();
        Eigen::VectorXd evalue = eigensolver.eigenvalues();

        // double alpha = (N+1)*(N+1)/2.0;
        // evalue *= alpha;

        outfile << "Eigenvalues: \n " << evalue << std::endl;

        return evalue;
}

int main(){
    // prepare a file for output
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }
    outfile << "---1D Schrodinger Equation Numerical Solution---" << std::endl;

    getEigen(100);
    getEigen(500);

    outfile.close();
    return 0;
}