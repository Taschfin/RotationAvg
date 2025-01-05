#include <visualization/displaying.h>

void showMeshes(const std::vector<std::string>& filepaths) {
	polyscope::init();
	loadAndDisplayMeshes(filepaths);
	polyscope::show();
}