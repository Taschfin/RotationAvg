#include <math/rotationOptimizer.h>
#include <Eigen/SVD>
#include <iostream>

Eigen::Matrix3d projectToSO(const Eigen::MatrixXd &gradient)
{
	Eigen::JacobiSVD<Eigen::Matrix3d> svd(gradient, Eigen::ComputeFullU | Eigen::ComputeFullV);
	return svd.matrixU() * svd.matrixV().transpose();
}

Eigen::MatrixXd RotationOptimizer::calculateRotationGradientAvg(
	const std::function<Eigen::MatrixXd(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &gradientFunction,
	const Eigen::MatrixXd &targetRotation)
{
	Eigen::MatrixXd gradientSum = Eigen::MatrixXd::Zero(rotations[0].rows(), rotations[0].cols());

	for (const Eigen::MatrixXd &rotation : rotations)
	{
		gradientSum += gradientFunction(targetRotation, rotation);
	}

	return gradientSum / rotations.size();
}

Eigen::MatrixXd RotationOptimizer::projectOnToTangentSpace(const Eigen::Matrix3d &R, const Eigen::Matrix3d &gradient)
{
	Eigen::Matrix3d RT_G = R.transpose() * gradient;
	Eigen::Matrix3d skew = 0.5 * (RT_G - RT_G.transpose());
	Eigen::Matrix3d tangentGradient = R * skew;

	return tangentGradient;
}

double RotationOptimizer::calculateDistanceSum(
	const std::function<double(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &distanceFunction,
	const Eigen::MatrixXd &targetRotation)
{
	double sum = 0.0;
	for (int i = 0; i < rotations.size(); ++i)
	{
		sum += distanceFunction(targetRotation, rotations[i]);
	}

	return sum;
}

Eigen::MatrixXd RotationOptimizer::optimizeOnManifold(
	const Eigen::MatrixXd &initialGuess,
	const std::function<double(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &distanceFunction,
	const std::function<Eigen::MatrixXd(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &gradientFunction)
{
	Eigen::MatrixXd currentRotation = initialGuess;
	int iteration = 0;
	double learningRateCopy = learningRate;
	double oldSumOfQuadraticDistances = calculateDistanceSum(distanceFunction, currentRotation);

	while (iteration < maxIterations)
	{

		Eigen::MatrixXd gradient = calculateRotationGradientAvg(gradientFunction, currentRotation);
		Eigen::MatrixXd tangentGradient = projectOnToTangentSpace(currentRotation, gradient);
		Eigen::MatrixXd nextRotation = currentRotation - learningRateCopy * tangentGradient;
		nextRotation = projectToSO(nextRotation);

		currentRotation = nextRotation;

		double newSumOfQuadraticDistances = calculateDistanceSum(distanceFunction, nextRotation);

		if (std::abs(newSumOfQuadraticDistances - oldSumOfQuadraticDistances) < threshhold)
		{
			std::cout << "Gradient Descent stoping at Iteration: " << iteration << std::endl;
			break;
		}

		if (newSumOfQuadraticDistances < oldSumOfQuadraticDistances)
		{
			learningRateCopy *= 1.1;
		}
		else
		{
			learningRateCopy *= 0.5;
		}

		oldSumOfQuadraticDistances = newSumOfQuadraticDistances;
		++iteration;
	}

	if (iteration == maxIterations)
	{
		std::cout << "Reached maximum iterations without convergence.\n";
	}

	return currentRotation;
}

Eigen::MatrixXd RotationOptimizer::optimizeOnFlag(
	const Eigen::MatrixXd &initialGuess,
	const std::function<double(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &distanceFunction,
	const std::function<Eigen::MatrixXd(const Eigen::MatrixXd &, const Eigen::MatrixXd &)> &gradientFunction)
{

	Eigen::MatrixXd currentFlag = initialGuess;
	int iteration = 0;
	double learningRateCopy = learningRate;
	double oldSumOfQuadraticDistances = calculateDistanceSum(distanceFunction, currentFlag);

	while (iteration < maxIterations)
	{

		Eigen::MatrixXd gradient = calculateRotationGradientAvg(gradientFunction, currentFlag);
		Eigen::MatrixXd nextFlag = currentFlag - learningRateCopy * gradient;
		nextFlag = projectToSO(nextFlag);
		currentFlag = nextFlag;

		double newSumOfQuadraticDistances = calculateDistanceSum(distanceFunction, nextFlag);

		if (std::abs(newSumOfQuadraticDistances - oldSumOfQuadraticDistances) < threshhold)
		{
			std::cout << "Gradient Descent stoping at Iteration: " << iteration << std::endl;
			break;
		}

		if (newSumOfQuadraticDistances < oldSumOfQuadraticDistances)
		{
			learningRateCopy *= 1.1;
		}
		else
		{
			learningRateCopy *= 0.5;
		}

		oldSumOfQuadraticDistances = newSumOfQuadraticDistances;
		++iteration;
	}

	if (iteration == maxIterations)
	{
		std::cout << "Reached maximum iterations without convergence.\n";
	}

	return currentFlag;
}