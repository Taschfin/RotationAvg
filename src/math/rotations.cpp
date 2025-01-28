#include <math/rotations.h>

double degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

Eigen::Matrix3d rotationMatrixAxisX(double angle_radians)
{
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << 1, 0, 0,
        0, cos(angle_radians), -sin(angle_radians),
        0, sin(angle_radians), cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d rotationMatrixAxisY(double angle_radians)
{
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), 0, sin(angle_radians),
        0, 1, 0,
        -sin(angle_radians), 0, cos(angle_radians);
    return rotation_matrix;
}

Eigen::Matrix3d rotationMatrixAxisZ(double angle_radians)
{
    Eigen::Matrix3d rotation_matrix;
    rotation_matrix << cos(angle_radians), -sin(angle_radians), 0,
        sin(angle_radians), cos(angle_radians), 0,
        0, 0, 1;
    return rotation_matrix;
}

Eigen::Matrix3d rotationMatrix(double angle_radians_x, double angle_radians_y, double angle_radians_z)
{
    return rotationMatrixAxisX(angle_radians_x) * rotationMatrixAxisY(angle_radians_y) * rotationMatrixAxisZ(angle_radians_z);
};

Eigen::MatrixXd rotateViaXAxis(const Eigen::MatrixXd &matrix, double angle_radians)
{
    return matrix * rotationMatrixAxisX(angle_radians);
};

Eigen::MatrixXd rotateViaYAxis(const Eigen::MatrixXd &matrix, double angle_radians)
{
    return matrix * rotationMatrixAxisY(angle_radians);
};

Eigen::MatrixXd rotateViaZAxis(const Eigen::MatrixXd &matrix, double angle_radians)
{
    return matrix * rotationMatrixAxisZ(angle_radians);
};

Eigen::MatrixXd rotateViaXY(const Eigen::MatrixXd &matrix, double angle_radians_x, double angle_radians_y)
{
    return matrix * (rotationMatrixAxisX(angle_radians_x) * rotationMatrixAxisY(angle_radians_y));
};

Eigen::MatrixXd rotateViaXZ(const Eigen::MatrixXd &matrix, double angle_radians_x, double angle_radians_z)
{
    return matrix * (rotationMatrixAxisY(angle_radians_x) * rotationMatrixAxisZ(angle_radians_z));
};

Eigen::MatrixXd rotateViaYZ(const Eigen::MatrixXd &matrix, double angle_radians_y, double angle_radians_z)
{
    return matrix * (rotationMatrixAxisZ(angle_radians_z) * rotationMatrixAxisY(angle_radians_y));
};

Eigen::MatrixXd generateRandomRotation()
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(1.94 * M_1_PI, 2 * M_PI);

    double alpha = dist(gen);
    double beta = dist(gen);
    double gamma = dist(gen);

    return rotationMatrixAxisX(alpha) * rotationMatrixAxisY(beta) * rotationMatrixAxisZ(gamma);
}

Eigen::Vector3d RotationAsPoint(const Eigen::Matrix3d &R)
{

    Eigen::AngleAxisd angleAxis(R);

    double theta = angleAxis.angle();

    Eigen::Vector3d axis = angleAxis.axis();
    Eigen::Vector3d point = theta * axis;

    return point;
}