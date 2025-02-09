
#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

double squaredChordalDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

Eigen::MatrixXd squaredChordalDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

double squaredQuaternionDistance(const Eigen::Matrix3d &R1, const Eigen::Matrix3d &R2);

Eigen::MatrixXd squaredQuaternionDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

double squaredDeviationFromIdentity(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

Eigen::MatrixXd squaredDeviationFromIdentityGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

double squaredGeodesicDistance(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);

Eigen::MatrixXd squaredGeodesicDistanceGradient(const Eigen::MatrixXd &R1, const Eigen::MatrixXd &R2);