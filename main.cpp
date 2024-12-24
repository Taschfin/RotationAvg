#include "libs/eigen-3.4.0/Eigen/Dense"

#include <iostream>

int main() {
    Eigen::MatrixXd mat(5,5);
    mat << 1, 2, 3, 4, 5,
		   6, 7, 8, 9, 10,
		   11, 12, 13, 14, 15,
		   16, 17, 18, 19, 20,
		   21, 22, 23, 24, 25;

    Eigen::MatrixXd result = mat.inverse();  // Transponierte Matrix
	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(mat);

	std::cout << "NEW2\n" << std::endl;
	std::cout << "Eigenwerte:\n" << solver.eigenvalues() << std::endl;
    std::cout << "Eigenvektoren:\n" << solver.eigenvectors() << std::endl;
    std::cout << "Matrix:\n" << mat << "\n";
    std::cout << "Transponierte Matrix:\n" << result << "\n";

    return 0;
}