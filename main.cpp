#include <Eigen/Dense>
#include <open3d/Open3D.h>
#include <iostream>

std::shared_ptr<open3d::geometry::LineSet> CreateGrid(double grid_size, int num_lines) {
    auto grid = std::make_shared<open3d::geometry::LineSet>();
    double half_size = grid_size * num_lines / 2.0;

    for (int i = -num_lines; i <= num_lines; ++i) {
        double pos = i * grid_size;
        grid->points_.emplace_back(Eigen::Vector3d(pos, 0, -half_size)); // Linie entlang X
        grid->points_.emplace_back(Eigen::Vector3d(pos, 0, half_size));
        grid->points_.emplace_back(Eigen::Vector3d(-half_size, 0, pos)); // Linie entlang Z
        grid->points_.emplace_back(Eigen::Vector3d(half_size, 0, pos));
    }

    for (int i = 0; i < grid->points_.size() / 2; ++i) {
        grid->lines_.emplace_back(Eigen::Vector2i(2 * i, 2 * i + 1));
    }

    return grid;
}

int main(int argc, char* argv[]) {
    using namespace open3d;

    if (argc < 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Mesh- oder Punktwolkenpfad> [Texturpfad]" << std::endl;
        return -1;
    }

    std::string file_path = argv[1];
    std::string texture_path = (argc > 2) ? argv[2] : "";

    // Versuche das Modell als Dreiecksmesh zu laden
    auto mesh = io::CreateMeshFromFile(file_path);

    if (mesh != nullptr && !mesh->vertices_.empty() && !mesh->triangles_.empty()) {
        std::cout << "Mesh geladen: " << file_path << std::endl;
        std::cout << "Anzahl der Dreiecke: " << mesh->triangles_.size() << std::endl;
        std::cout << "Anzahl der Vertices: " << mesh->vertices_.size() << std::endl;

        // Textur laden, falls angegeben
        if (!texture_path.empty()) {
            auto texture = io::CreateImageFromFile(texture_path);
            if (texture != nullptr) {
                std::cout << "Textur geladen: " << texture_path << std::endl;
                mesh->textures_.push_back(*texture);
            } else {
                std::cerr << "Fehler beim Laden der Textur!" << std::endl;
            }
        }

        // Grid hinzufügen
        auto grid = CreateGrid(0.1, 10);
        visualization::DrawGeometries({mesh, grid}, "Mesh mit Textur und Gitter", 800, 600);
    } else {
        // Versuche das Modell als Punktwolke zu laden
        auto cloud = io::CreatePointCloudFromFile(file_path);

        if (cloud != nullptr && !cloud->points_.empty()) {
            std::cout << "Punktwolke geladen: " << file_path << std::endl;
            std::cout << "Anzahl der Punkte: " << cloud->points_.size() << std::endl;

            auto grid = CreateGrid(0.1, 10);
            visualization::DrawGeometries({cloud, grid}, "Punktwolke mit Gitter", 800, 600);
        } else {
            std::cerr << "Fehler: Datei konnte weder als Mesh noch als Punktwolke geladen werden." << std::endl;
            return -1;
        }
    }

    return 0;
}
