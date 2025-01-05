#pragma once

#include <Eigen/Dense>

Eigen::Matrix3d RotationMatrixAxisX(double angle_radians);

Eigen::Matrix3d RotationMatrixAxisY(double angle_radians);

Eigen::Matrix3d RotationMatrixAxisZ(double angle_radians);

Eigen::MatrixXd RotateViaXAxis(const Eigen::MatrixXd& matrix, double angle_radians);

Eigen::MatrixXd RotateViaYAxis(const Eigen::MatrixXd& matrix, double angle_radians);

Eigen::MatrixXd RotateViaZAxis(const Eigen::MatrixXd& matrix, double angle_radians);

