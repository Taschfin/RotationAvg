#include <helpers/rotations.h>
#include <cmath>

Eigen::Matrix3d RotationMatrixAxisX(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << 1, 0, 0,
                       0, cos(angle_radians), -sin(angle_radians),
                       0, sin(angle_radians), cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d RotationMatrixAxisY(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), 0, sin(angle_radians),
                       0, 1, 0,
                      -sin(angle_radians), 0, cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d RotationMatrixAxisZ(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), -sin(angle_radians), 0,
                       sin(angle_radians), cos(angle_radians), 0,
                       0, 0, 1;
    return rotation_matrix;
}

Eigen::MatrixXd RotateViaXAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * RotationMatrixAxisX(angle_radians).transpose();
};

Eigen::MatrixXd RotateViaYAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * RotationMatrixAxisY(angle_radians).transpose();
};

Eigen::MatrixXd RotateViaZAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * RotationMatrixAxisZ(angle_radians).transpose();
};

Eigen::MatrixXd RotateViaXY(const Eigen::MatrixXd& matrix, double angle_radians_x, double angle_radians_y) {
	return matrix * RotationMatrixAxisX(angle_radians_x).transpose() * RotationMatrixAxisY(angle_radians_y).transpose();
};

Eigen::MatrixXd RotateViaXZ(const Eigen::MatrixXd& matrix, double angle_radians_x, double angle_radians_z) {
	return matrix * RotationMatrixAxisY(angle_radians_x).transpose() * RotationMatrixAxisZ(angle_radians_z).transpose();
};

Eigen::MatrixXd RotateViaYZ(const Eigen::MatrixXd& matrix, double angle_radians_y, double angle_radians_z) {
	return matrix * RotationMatrixAxisZ(angle_radians_z).transpose() * RotationMatrixAxisY(angle_radians_y).transpose();
};


