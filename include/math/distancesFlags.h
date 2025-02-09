#pragma once

#include <Eigen/Dense>

double squaredChordalDistanceFlag(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

Eigen::MatrixXd squaredChordalDistanceGradientFlag(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);