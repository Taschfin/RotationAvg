#include <polyscope/polyscope.h>
#include <polyscope/surface_mesh.h>
#include <tiny_obj_loader.h>
#include <Eigen/Dense>
#include <iostream>
#include <string>

void loadAndDisplayMesh(const std::string& filepath) {
    // Laden des OBJ-Modells
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str())) {
        std::cerr << "Fehler beim Laden des Meshes: " << warn << err << std::endl;
        return;
    }

    std::cout << "Mesh geladen: " << filepath << std::endl;

    // Daten für Polyscope vorbereiten
    Eigen::MatrixXd vertices(attrib.vertices.size() / 3, 3); // Vertex-Matrix
    Eigen::MatrixXi faces; // Face-Matrix

    // Vertices einlesen
    for (size_t i = 0; i < attrib.vertices.size(); i += 3) {
        vertices.row(i / 3) << attrib.vertices[i], attrib.vertices[i + 1], attrib.vertices[i + 2];
    }

    // Anzahl der Dreiecke berechnen
    size_t num_faces = 0;
    for (const auto& shape : shapes) {
        num_faces += shape.mesh.indices.size() / 3;
    }

    //std::cout << "Shapes: " << shapes.size() << " num_faces " << num_faces << " indices " << shapes[0].mesh.indices.size() << std::endl;

    // Faces einlesen
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

    // Mesh zu Polyscope hinzufügen
    polyscope::registerSurfaceMesh("Mesh", vertices, faces);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Pfad zur OBJ-Datei>" << std::endl;
        return -1;
    }

    std::string filepath = argv[1];

    // Polyscope initialisieren
    polyscope::init();

    // Mesh laden und anzeigen
    loadAndDisplayMesh(filepath);

    // Hauptschleife von Polyscope starten
    polyscope::show();

    return 0;
}
