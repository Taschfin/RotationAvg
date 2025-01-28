#pragma once

#include <random>
#include <cmath>
#include <iostream>

#include <Eigen/Dense>

double degreesToRadians(double degrees);

Eigen::Matrix3d rotationMatrixAxisX(double angle_radians);

Eigen::Matrix3d rotationMatrixAxisY(double angle_radians);

Eigen::Matrix3d rotationMatrixAxisZ(double angle_radians);

Eigen::Matrix3d rotationMatrix(double angle_radians_x, double angle_radians_y, double angle_radians_z);

Eigen::MatrixXd rotateViaXAxis(const Eigen::MatrixXd &matrix, double angle_radians);

Eigen::MatrixXd rotateViaYAxis(const Eigen::MatrixXd &matrix, double angle_radians);

Eigen::MatrixXd rotateViaZAxis(const Eigen::MatrixXd &matrix, double angle_radians);

Eigen::MatrixXd rotateViaXY(const Eigen::MatrixXd &matrix, double angle_radians_x, double angle_radians_y);

Eigen::MatrixXd rotateViaXZ(const Eigen::MatrixXd &matrix, double angle_radians_x, double angle_radians_z);

Eigen::MatrixXd rotateViaYZ(const Eigen::MatrixXd &matrix, double angle_radians_y, double angle_radians_z);

Eigen::MatrixXd generateRandomRotation();

Eigen::Vector3d RotationAsPoint(const Eigen::Matrix3d &R);