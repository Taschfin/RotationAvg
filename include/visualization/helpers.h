#pragma once

#include <format>

#include <math/rotations.h>
#include <visualization/loading.h>

#include <Eigen/Dense>

#include <polyscope/point_cloud.h>
#include <polyscope/curve_network.h>

void addRandomRotations(std::vector<Eigen::MatrixXd> &rotations, int numOfRotations);

std::pair<std::vector<std::array<double, 3>>, std::vector<std::array<size_t, 2>>> getLinePointsAndEdges(const Eigen::Matrix3d &matrix);

std::pair<std::vector<std::array<double, 3>>, std::vector<std::array<size_t, 3>>> getPlanePointsAndFaces(const Eigen::Matrix3d &matrix);

polyscope::CurveNetwork *displayLineFromMatrix(const Eigen::Matrix3d &matrix, int num, bool enabled = false);

polyscope::SurfaceMesh *displayPlaneFromMatrix(const Eigen::Matrix3d &matrix, int num, bool enabled = false);

void removeDisplayedFlag(std::string lineName, std::string planeName);

void removeDisplayedFlags(std::vector<Eigen::MatrixXd> &rotations, std::vector<polyscope::CurveNetwork *> &lines, std::vector<polyscope::SurfaceMesh *> &planes);

void resetMesh(std::string mesh_name);