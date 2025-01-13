#include <visualization/loading.h>
#include <helpers/rotations.h>

std::unordered_map<std::string, MeshData> Meshes;

std::string loadAndDisplayMesh(const std::string &filepath, int &mesh_count)
{

    // Laden des OBJ-Modells
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    mesh_count++;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str()))
    {
        std::cerr << "Error while loading mesh: " << warn << err << std::endl;
        return "";
    }

    std::cout << "Loading Mesh " << mesh_count << ": " << filepath << std::endl;

    Eigen::MatrixXd vertices = centerMeshAtOrigin(vectorToMatrix(attrib.vertices, attrib.vertices.size() / 3, 3));

    Eigen::MatrixXi faces;

    size_t num_faces = 0;
    for (const auto &shape : shapes)
    {
        num_faces += shape.mesh.indices.size() / 3;
    }

    faces.resize(num_faces, 3);

    size_t face_index = 0;
    for (const auto &shape : shapes)
    {
        for (size_t i = 0; i < shape.mesh.indices.size(); i += 3)
        {
            faces(face_index, 0) = shape.mesh.indices[i + 0].vertex_index;
            faces(face_index, 1) = shape.mesh.indices[i + 1].vertex_index;
            faces(face_index, 2) = shape.mesh.indices[i + 2].vertex_index;
            face_index++;
        }
    }

    std::string mesh_name = "Mesh" + std::to_string(mesh_count);
    polyscope::registerSurfaceMesh(mesh_name, vertices, faces);
    Meshes[mesh_name] = {vertices, faces, 0.0, 0.0, 0.0, 0.5, 0.5, 0.5};
    return mesh_name;
}

void resetMeshProperties(const std::string &mesh_name)
{
    Meshes[mesh_name].rotationX = 0.0;
    Meshes[mesh_name].rotationY = 0.0;
    Meshes[mesh_name].rotationZ = 0.0;
    Meshes[mesh_name].scaleX = 0.5;
    Meshes[mesh_name].scaleY = 0.5;
    Meshes[mesh_name].scaleZ = 0.5;
}

std::vector<std::string> loadMeshes(const std::vector<std::string> &filepaths)
{
    int mesh_count = 0;
    std::vector<std::string> mesh_names;

    for (const auto &filepath : filepaths)
    {
        std::string mesh_name = loadAndDisplayMesh(filepath, mesh_count);
        if (mesh_name == "")
        {
            continue;
        }
        mesh_names.push_back(mesh_name);
    }

    return mesh_names;
}