#pragma once

#include <math/rotations.h>

Eigen::Matrix3d convexCombination(const Eigen::Matrix3d &matrix1, const Eigen::Matrix3d &matrix2, double alpha);

Eigen::MatrixXd convexCombinationXY(const Eigen::MatrixXd &matrix, double angle1, double angle2, double alpha);

Eigen::MatrixXd convexCombinationOrthoXY(const Eigen::MatrixXd &matrix, double angle1, double angle2, double alpha);