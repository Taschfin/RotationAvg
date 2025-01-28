
#pragma once

#include <Eigen/Dense>

double squaredChordalDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

Eigen::MatrixXd squaredChordalDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

double geodesicDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2);

double spectralDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2);