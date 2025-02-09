#include <visualization/helpers.h>

void addRandomRotations(std::vector<Eigen::MatrixXd> &rotations, int numOfRotations)
{
	for (int i = 0; i < numOfRotations; ++i)
	{
		Eigen::Matrix3d rotation = generateRandomRotation();
		rotations.push_back(rotation);
	}
}

void resetMesh(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	resetMeshProperties(mesh_name);

	mesh->updateVertexPositions(meshData.vertices);
}

std::pair<std::vector<std::array<double, 3>>, std::vector<std::array<size_t, 2>>> getLinePointsAndEdges(const Eigen::Matrix3d &matrix)
{
	Eigen::Vector3d direction = matrix.col(0).normalized();

	double tMax = 2.0;
	Eigen::Vector3d point1 = -tMax * direction;
	Eigen::Vector3d point2 = tMax * direction;

	std::vector<std::array<double, 3>> points = {
		{point1.x(), point1.y(), point1.z()},
		{point2.x(), point2.y(), point2.z()}};
	std::vector<std::array<size_t, 2>> edges = {
		{0, 1}};

	return {points, edges};
}

std::pair<std::vector<std::array<double, 3>>, std::vector<std::array<size_t, 3>>> getPlanePointsAndFaces(const Eigen::Matrix3d &matrix)
{
	Eigen::Vector3d u = matrix.col(0);
	Eigen::Vector3d v = matrix.col(1);

	std::vector<std::array<double, 3>> points = {
		{u.x() + v.x(), u.y() + v.y(), u.z() + v.z()},
		{u.x() - v.x(), u.y() - v.y(), u.z() - v.z()},
		{-u.x() - v.x(), -u.y() - v.y(), -u.z() - v.z()},
		{-u.x() + v.x(), -u.y() + v.y(), -u.z() + v.z()}};

	std::vector<std::array<size_t, 3>> faces = {
		{0, 1, 2},
		{0, 2, 3}};

	return {points, faces};
}

polyscope::CurveNetwork *displayLineFromMatrix(const Eigen::Matrix3d &matrix, int num, bool enabled)
{
	auto [points, edges] = getLinePointsAndEdges(matrix);

	auto *line = polyscope::registerCurveNetwork(std::format("LineFlag {}", num), points, edges);
	line->setRadius(0.01);
	line->setEnabled(enabled);

	return line;
}

polyscope::SurfaceMesh *displayPlaneFromMatrix(const Eigen::Matrix3d &matrix, int num, bool enabled)
{
	auto [psVertices, faces] = getPlanePointsAndFaces(matrix);

	auto *plane = polyscope::registerSurfaceMesh(std::format("PlaneFlag {}", num), psVertices, faces);
	plane->setEnabled(enabled);

	return plane;
}

void removeDisplayedFlag(std::string lineName, std::string planeName)
{
	if (polyscope::hasCurveNetwork(lineName))
		polyscope::removeCurveNetwork(lineName);

	if (polyscope::hasSurfaceMesh(planeName))
		polyscope::removeSurfaceMesh(planeName);
}

void removeDisplayedFlags(std::vector<Eigen::MatrixXd> &rotations, std::vector<polyscope::CurveNetwork *> &lines, std::vector<polyscope::SurfaceMesh *> &planes)
{
	for (int i = 0; i < rotations.size(); i++)
	{
		removeDisplayedFlag(lines[i]->name, planes[i]->name);
	}

	lines.clear();
	planes.clear();
	rotations.clear();
}