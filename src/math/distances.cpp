#include <math/distances.h>

// Chordal Distance

double squaredChordalDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	Eigen::Matrix3d diff = R1 - R2;
	return diff.squaredNorm();
}

Eigen::MatrixXd squaredChordalDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	return 2 * (R1 - R2);
}

// Deviation from the Identity Matrix

double squaredDeviationFromIdentity(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	int N = R1.rows();
	return 2 * (N - (R1 * R2.transpose()).trace());
	;
}

Eigen::MatrixXd squaredDeviationFromIdentityGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	return -2 * R2;
}

// Geodesic Distance

double squaredGeodesicDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
	Eigen::MatrixXd X = R1 * R2.transpose();

	Eigen::JacobiSVD<Eigen::MatrixXd> svd(X, Eigen::ComputeFullU | Eigen::ComputeFullV);
	Eigen::MatrixXd S = svd.singularValues().asDiagonal();
	Eigen::MatrixXd logX = svd.matrixU() * S.array().log().matrix().asDiagonal() * svd.matrixV().transpose();

	return logX.squaredNorm();
}

Eigen::MatrixXd csquaredGeodesicDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2)
{
}
