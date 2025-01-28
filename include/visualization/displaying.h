#pragma once

#include <format>

#include <visualization/loading.h>
#include <math/convexCombination.h>
#include <math/rotationOptimizer.h>

#include <polyscope/polyscope.h>
#include <polyscope/point_cloud.h>
#include <polyscope/curve_network.h>

void showMeshes(const std::vector<std::string> &filepaths);

void initializeElements(const std::vector<std::string> &mesh_names);

void meshTab(const std::vector<std::string> &mesh_names);

void rotationSlider(std::string mesh_name);

void convexCombination(std::string mesh_name);

void optimalRotation(std::string mesh_name);

void displayFlags();

void generateRandomRotationsAndDisplay(int numOfRotations);

void addRandomRotations(int numOfRotations);

void resetMesh(std::string mesh_name);

void displayLineFromMatrix(const Eigen::Matrix3d &matrix);

void displayPlaneFromMatrix(const Eigen::Matrix3d &matrix);