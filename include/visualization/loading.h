#pragma once

#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>
#include <tiny_obj_loader.h>
#include <Eigen/Dense>

#include <globals.h>
#include <helpers/transformations.h>
#include <math/rotations.h>

struct MeshData
{
    Eigen::MatrixXd vertices;
    Eigen::MatrixXi faces;
    float rotationX = 0.0;
    float rotationY = 0.0;
    float rotationZ = 0.0;
    float scaleX = 1.0;
    float scaleY = 1.0;
    float scaleZ = 1.0;
};

extern std::unordered_map<std::string, MeshData> Meshes;

std::string loadAndDisplayMesh(const std::string &filepath, int &mesh_count);

void resetMeshProperties(const std::string &mesh_name);

std::vector<std::string> loadMeshes(const std::vector<std::string> &filepaths);