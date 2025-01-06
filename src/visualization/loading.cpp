#include <visualization/loading.h>
#include <helpers/rotations.h>

bool loadAndDisplayMesh(const std::string& filepath, int& mesh_count) {

		// Laden des OBJ-Modells
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

		mesh_count++;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
            std::cerr << "Error while loading mesh: " << warn << err << std::endl;
			return false;
        }

        std::cout << "Loading Mesh " << mesh_count << ": " << filepath << std::endl;

		Eigen::MatrixXd vertices;

		if (mesh_count == 1) {
        	vertices = rotateViaXAxis(vectorToMatrix(attrib.vertices, attrib.vertices.size()/3, 3), M_PI/2);
		}
		else if (mesh_count == 2)
		{
			vertices = rotateViaYAxis(vectorToMatrix(attrib.vertices, attrib.vertices.size()/3, 3), M_PI);
		}
		else if (mesh_count == 3)
		{
			vertices = rotateViaZAxis(vectorToMatrix(attrib.vertices, attrib.vertices.size()/3, 3), M_PI/2);
		}
		else if (mesh_count == 4){
			vertices = rotateViaXZ(vectorToMatrix(attrib.vertices, attrib.vertices.size()/3, 3), M_PI/2, M_PI/2);
		}
		else {
			vertices =vectorToMatrix(attrib.vertices, attrib.vertices.size()/3, 3);
		}

        Eigen::MatrixXi faces;


        size_t num_faces = 0;
        for (const auto& shape : shapes) {
            num_faces += shape.mesh.indices.size() / 3;
        }

        faces.resize(num_faces, 3);

        size_t face_index = 0;
        for (const auto& shape : shapes) {
            for (size_t i = 0; i < shape.mesh.indices.size(); i += 3) {
                faces(face_index, 0) = shape.mesh.indices[i + 0].vertex_index;
                faces(face_index, 1) = shape.mesh.indices[i + 1].vertex_index;
                faces(face_index, 2) = shape.mesh.indices[i + 2].vertex_index;
                face_index++;
            }
        }

        std::string mesh_name = "Mesh" + std::to_string(mesh_count);
        polyscope::registerSurfaceMesh(mesh_name, vertices, faces);
		return true;
}

void loadAndDisplayMeshes(const std::vector<std::string>& filepaths) {
	int mesh_count = 0;

	for (const auto& filepath : filepaths) {
		if (!loadAndDisplayMesh(filepath, mesh_count)){
			continue;
		}
	}
}