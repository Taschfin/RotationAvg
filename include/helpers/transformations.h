#pragma once

#include <Eigen/Dense>

Eigen::MatrixXd vectorToMatrix(const std::vector<float> &vector, int rows, int cols);

Eigen::MatrixXd centerMeshAtOrigin(const Eigen::MatrixXd &vertices);