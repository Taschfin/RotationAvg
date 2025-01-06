
#include <Eigen/Dense>
#include <iostream>
#include <string>
#include <thread>

#include <visualization/displaying.h>
#include <helpers/rotations.h>

/*void handleUserInput() {
    while (true) {
        std::string meshName;
        double angleX, angleY, angleZ;

        std::cout << "Geben Sie den Mesh-Namen ein (oder 'exit' zum Beenden): ";
        std::cin >> meshName;

        if (meshName == "exit") break;

        // Polyscope-Objekt holen
        auto* mesh = polyscope::getSurfaceMesh(meshName);
        if (!mesh) {
            std::cout << "Mesh nicht gefunden!" << std::endl;
            continue;
        }

        std::cout << "Geben Sie die Rotationswinkel (in Grad) für X, Y, Z ein: ";
        std::cin >> angleX >> angleY >> angleZ;

        // Winkel in Radiant umrechnen
        angleX = angleX * M_PI / 180.0;
        angleY = angleY * M_PI / 180.0;
        angleZ = angleZ * M_PI / 180.0;

        std::vector<float> verticesVector;
        for (size_t i = 0; i < mesh->nVertices(); ++i) {
            auto pos = mesh->vertexPositions.getValue(i);
            verticesVector.push_back(pos.x);
            verticesVector.push_back(pos.y);
            verticesVector.push_back(pos.z);
        }

        Eigen::MatrixXd vertices = vectorToMatrix(verticesVector, mesh->nVertices(), 3);
        vertices = rotateViaXAxis(rotateViaXY(vertices, angleX, angleY), angleZ);
        mesh->updateVertexPositions(vertices);

        std::cout << "Mesh '" << meshName << "' erfolgreich rotiert." << std::endl;
    }
}*/

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Path to OBJ-File 1> <Path to OBJ-File 2> ..." << std::endl;
        return -1;
    }

    std::vector<std::string> filepaths;
    for (int i = 1; i < argc; ++i) {
        filepaths.push_back(argv[i]);
    }

    //std::thread inputThread(handleUserInput);
    showMeshes(filepaths);
    //inputThread.join();

    return 0;
}
