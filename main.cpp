#include <Eigen/Dense>

#include <iostream>
#include <open3d/Open3D.h>

int main() {
    using namespace open3d;
    
    // Datei des Stanford Bunnys (Pfad anpassen!)
    std::string file_path = "bunny.obj";

    // Mesh-Objekt erstellen
    std::shared_ptr<geometry::TriangleMesh> mesh = io::CreateMeshFromFile(file_path);

    if (mesh == nullptr || mesh->vertices_.empty()) {
        std::cerr << "Fehler: Mesh konnte nicht geladen werden!" << std::endl;
        return -1;
    }

    // Informationen über das Mesh ausgeben
    std::cout << "Mesh geladen: " << file_path << std::endl;
    std::cout << "Anzahl der Dreiecke: " << mesh->triangles_.size() << std::endl;
    std::cout << "Anzahl der Vertices: " << mesh->vertices_.size() << std::endl;

    // Mesh visualisieren
    visualization::DrawGeometries({mesh}, "Stanford Bunny", 800, 600);

    return 0;
}
