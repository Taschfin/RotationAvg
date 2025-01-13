#include <helpers/convexCombination.h>
#include <iostream>

Eigen::Matrix3d convexCombination(const Eigen::Matrix3d &matrix1, const Eigen::Matrix3d &matrix2, double alpha)
{
	return alpha * matrix1 + (1 - alpha) * matrix2;
}

Eigen::MatrixXd convexCombinationXY(const Eigen::MatrixXd &matrix, double angle1, double angle2, double alpha)
{
	Eigen::Matrix3d matrix1 = rotationMatrixAxisX(degreesToRadians(angle1));
	Eigen::Matrix3d matrix2 = rotationMatrixAxisY(degreesToRadians(angle2));

	Eigen::MatrixXd convexMatrix = convexCombination(matrix1, matrix2, alpha);

	return matrix * convexMatrix;
}

Eigen::MatrixXd convexCombinationOrthoXY(const Eigen::MatrixXd &matrix, double angle1, double angle2, double alpha)
{
	Eigen::Matrix3d matrix1 = rotationMatrixAxisX(degreesToRadians(angle1));
	Eigen::Matrix3d matrix2 = rotationMatrixAxisY(degreesToRadians(angle2));

	Eigen::MatrixXd convexMatrix = convexCombination(matrix1, matrix2, alpha);

	Eigen::HouseholderQR<Eigen::MatrixXd> qr(convexMatrix);
	Eigen::MatrixXd orthonormalizedMatrix = qr.householderQ();

	std::cout << orthonormalizedMatrix << std::endl;

	return matrix * orthonormalizedMatrix;
}