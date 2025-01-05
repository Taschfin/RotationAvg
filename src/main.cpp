
#include <Eigen/Dense>
#include <iostream>
#include <string>

#include <visualization/displaying.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Verwendung: " << argv[0] << " <Path to OBJ-File 1> <Path to OBJ-File 2> ..." << std::endl;
        return -1;
    }

    std::vector<std::string> filepaths;
    for (int i = 1; i < argc; ++i) {
        filepaths.push_back(argv[i]);
    }

    showMeshes(filepaths);

    return 0;
}
