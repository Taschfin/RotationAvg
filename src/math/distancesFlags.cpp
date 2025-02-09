#include <math/distancesFlags.h>

double squaredChordalDistanceFlag(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	double distance = 0.0;
	for (int j = 0; j < R1.cols(); ++j)
	{
		Eigen::MatrixXd R1j = R1.block(0, 0, R1.rows(), j + 1);
		Eigen::MatrixXd R2j = R2.block(0, 0, R2.rows(), j + 1);
		distance += (j + 1) - (R1j.transpose() * R2j * R2j.transpose() * R1j).trace();
	}
	return distance;
}

Eigen::MatrixXd squaredChordalDistanceGradientFlag(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	Eigen::MatrixXd grad = Eigen::MatrixXd::Zero(R1.rows(), R1.cols());
	for (int j = 0; j < R1.cols(); ++j)
	{
		Eigen::MatrixXd R1j = R1.block(0, 0, R1.rows(), j + 1);
		Eigen::MatrixXd R2j = R2.block(0, 0, R2.rows(), j + 1);
		grad.block(0, 0, R1.rows(), j + 1) += -2 * R2j * R2j.transpose() * R1j;
	}
	return grad;
}
