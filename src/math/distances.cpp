#include <math/distances.h>

double squaredChordalDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	Eigen::Matrix3d diff = R1 - R2;
	double frobeniusNorm = diff.norm();

	return pow(frobeniusNorm, 2);
}

Eigen::MatrixXd squaredChordalDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	return 2 * (R1 - R2);
}

double geodesicDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2)
{
	double cosTheta = ((R1.transpose() * R2).trace() - 1) / 2;
	cosTheta = std::max(-1.0, std::min(1.0, cosTheta));

	return std::acos(cosTheta);
}

double spectralDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2)
{
	Eigen::Matrix3d diff = R1.transpose() * R2 - Eigen::MatrixXd::Identity(3, 3);

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(diff, Eigen::ComputeThinU | Eigen::ComputeThinV);
	return svd.singularValues()(0);
}

/*double projectionDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2)
{
	Eigen::Matrix3d diff = R1.transpose() * R2 - Eigen::MatrixXd::Identity(3, 3);
	double dist =
}*/