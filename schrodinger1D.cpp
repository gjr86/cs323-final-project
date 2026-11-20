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
    // choice of x limits are completely arbitrary at this point
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

Eigen::VectorXd RQI(MatrixXd H){

    return Eigen::VectorXd{};
}

Eigen::VectorXd getEigen(int N){
    outfile << std::endl << "N=" << N << std::endl;

    Eigen::MatrixXd H = buildHamiltonian(N);

    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(H);
    if (eigensolver.info() != Eigen::Success) abort();

    Eigen::VectorXd evalue = (eigensolver.eigenvalues()).head(50);
    outfile << evalue << std::endl;

    return evalue;
}

int main(){
    if (!outfile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return 1;
    }

    int i = 100;
    while(i<=1000){
        getEigen(i);
        i+=100;
    }

    outfile.close();
    return 0;
}