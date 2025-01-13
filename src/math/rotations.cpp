#include <helpers/rotations.h>
#include <cmath>

double degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

Eigen::Matrix3d rotationMatrixAxisX(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << 1, 0, 0,
                       0, cos(angle_radians), -sin(angle_radians),
                       0, sin(angle_radians), cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d rotationMatrixAxisY(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), 0, sin(angle_radians),
                       0, 1, 0,
                      -sin(angle_radians), 0, cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d rotationMatrixAxisZ(double angle_radians) {
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), -sin(angle_radians), 0,
                       sin(angle_radians), cos(angle_radians), 0,
                       0, 0, 1;
    return rotation_matrix;
}

Eigen::MatrixXd rotateViaXAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * rotationMatrixAxisX(angle_radians).transpose();
};

Eigen::MatrixXd rotateViaYAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * rotationMatrixAxisY(angle_radians).transpose();
};

Eigen::MatrixXd rotateViaZAxis(const Eigen::MatrixXd& matrix, double angle_radians) {
	return matrix * rotationMatrixAxisZ(angle_radians).transpose();
};

Eigen::MatrixXd rotateViaXY(const Eigen::MatrixXd& matrix, double angle_radians_x, double angle_radians_y) {
	return matrix * (rotationMatrixAxisX(angle_radians_x).transpose() * rotationMatrixAxisY(angle_radians_y).transpose());
};

Eigen::MatrixXd rotateViaXZ(const Eigen::MatrixXd& matrix, double angle_radians_x, double angle_radians_z) {
	return matrix * (rotationMatrixAxisY(angle_radians_x).transpose() * rotationMatrixAxisZ(angle_radians_z).transpose());
};

Eigen::MatrixXd rotateViaYZ(const Eigen::MatrixXd& matrix, double angle_radians_y, double angle_radians_z) {
	return matrix * (rotationMatrixAxisZ(angle_radians_z).transpose() * rotationMatrixAxisY(angle_radians_y).transpose());
};


