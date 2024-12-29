#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Fehler: Kein Dateipfad angegeben!" << std::endl;
        return -1;
    }

    std::string file_path = argv[1];

    // Assimp Importer
    Assimp::Importer importer;

    // Lade das Modell
    const aiScene* scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipWindingOrder);

    // Überprüfe, ob das Modell erfolgreich geladen wurde
    if (!scene) {
        std::cerr << "Fehler beim Laden der Datei: " << importer.GetErrorString() << std::endl;
        return -1;
    }

    std::cout << "Mesh geladen: " << file_path << std::endl;
    std::cout << "Anzahl der Meshes: " << scene->mNumMeshes << std::endl;

    // Weitere Verarbeitung der Mesh-Daten, z. B. Visualisierung

    return 0;
}
