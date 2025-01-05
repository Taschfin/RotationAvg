# pragma once

#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>
#include <tiny_obj_loader.h>
#include <Eigen/Dense>

#include <helpers/transformations.h>

bool loadAndDisplayMesh(const std::string& filepath, int& mesh_count);

void loadAndDisplayMeshes(const std::vector<std::string>& filepaths);