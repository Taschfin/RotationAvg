#pragma once

#include <format>

#include <visualization/loading.h>
#include <math/convexCombination.h>
#include <math/rotationOptimizer.h>
#include <math/distancesFlags.h>
#include <visualization/helpers.h>

#include <polyscope/polyscope.h>
#include <polyscope/point_cloud.h>
#include <polyscope/curve_network.h>

void showMeshes(const std::vector<std::string> &filepaths);

void initializeElements(const std::vector<std::string> &mesh_names);

void meshTab(const std::vector<std::string> &mesh_names);

void rotationSlider(std::string mesh_name);

void convexCombination(std::string mesh_name);

void optimalRotationOnManifold(std::string mesh_name);

void optimalRotationOnFlag();

void displayFlags();
