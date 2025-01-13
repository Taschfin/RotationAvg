#pragma once

#include <format>

#include <visualization/loading.h>
#include <helpers/convexCombination.h>

void showMeshes(const std::vector<std::string> &filepaths);

void initializeElements(const std::vector<std::string> &mesh_names);

void meshTab(const std::vector<std::string> &mesh_names);

void rotationSlider(std::string mesh_name);

void convexCombination(std::string mesh_name);

void resetMesh(std::string mesh_name);