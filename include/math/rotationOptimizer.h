#pragma once

#include <functional>
#include <iostream>

#include <Eigen/Dense>
#include <math/distances.h>
#include <unsupported/Eigen/MatrixFunctions>
#include <polyscope/polyscope.h>
#include <polyscope/point_cloud.h>

class RotationOptimizer
{
public:
	RotationOptimizer(std::vector<Eigen::MatrixXd> &rotations, double learningRate, int maxIterations, double threshhold)
		: rotations(rotations), learningRate(learningRate), maxIterations(maxIterations), threshhold(threshhold) {}

	Eigen::MatrixXd optimizeOnManifold(
		const Eigen::MatrixXd &initialGuess,
		const std::function<double(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &distanceFunction,
		const std::function<Eigen::MatrixXd(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &gradientFunction);

	double calculateDistanceSum(const std::function<double(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &distanceFunction,
								const Eigen::MatrixXd &targetRotation);

	Eigen::MatrixXd calculateRotationGradientAvg(
		const std::function<Eigen::MatrixXd(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &gradientFunction,
		const Eigen::MatrixXd &targetRotation);

	Eigen::MatrixXd projectOnToTangentSpace(const Eigen::Matrix3d &R,
											const Eigen::Matrix3d &gradient);

private:
	std::vector<Eigen::MatrixXd> &rotations;
	double learningRate;
	int maxIterations;
	double threshhold;
};
