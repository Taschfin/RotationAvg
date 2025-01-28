#include <visualization/displaying.h>

// GLOBAL VARIABLES
// Gradient Descent

std::vector<Eigen::Vector3d> rotationsPoints;
std::vector<Eigen::MatrixXd> rotations;
float rotationXOptimization = 0.0;
float rotationYOptimization = 0.0;
float rotationZOptimization = 0.0;

// Flags

float rotationXFlag = 0.0;
float rotationYFlag = 0.0;
float rotationZFlag = 0.0;

void showMeshes(const std::vector<std::string> &filepaths)
{
	polyscope::init();
	std::vector<std::string> mesh_names = loadMeshes(filepaths);
	polyscope::state::userCallback = [&]()
	{
		meshTab(mesh_names);
	};
	polyscope::show();
}

void meshTab(const std::vector<std::string> &mesh_names)
{
	if (ImGui::BeginTabBar("Tabs"))
	{
		for (const auto &mesh_name : mesh_names)
		{
			if (ImGui::BeginTabItem(mesh_name.c_str()))
			{

				ImGui::Dummy(ImVec2(0.0f, 10.0f)); // spacing

				static int selectedItem = 0;
				std::vector<std::string> items = {"Rotation", "Convexcombination", "Optimial Rotation"};

				ImGui::Text("Select a function:");
				if (ImGui::BeginCombo("Functions", items[selectedItem].c_str()))
				{
					for (int i = 0; i < items.size(); i++)
					{
						bool isSelected = (selectedItem == i);
						if (ImGui::Selectable(items[i].c_str(), isSelected))
						{
							selectedItem = i;
							resetMesh(mesh_name);
						}
						if (isSelected)
						{
							ImGui::SetItemDefaultFocus();
						}
					}
					ImGui::EndCombo();
				}

				ImGui::Dummy(ImVec2(0.0f, 20.0f)); // spacing

				switch (selectedItem)
				{
				case 0:
					rotationSlider(mesh_name);
					break;
				case 1:
					convexCombination(mesh_name);
					break;
				case 2:
					optimalRotation(mesh_name);
					break;
				default:
					break;
				}

				ImGui::EndTabItem();
			}
		}

		if (ImGui::BeginTabItem("Display Flags"))
		{
			displayFlags();
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
}

void rotationSlider(std::string mesh_name)
{

	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	// Rotation around X-Axis
	ImGui::SliderFloat("Rotation Angle (X)", &meshData.rotationX, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesX = rotateViaXAxis(meshData.vertices, degreesToRadians(meshData.rotationX));

	// Rotation around Y-Axis
	ImGui::SliderFloat("Rotation Angle (Y)", &meshData.rotationY, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesY = rotateViaYAxis(rotatedVerticesX, degreesToRadians(meshData.rotationY));

	// Rotation around Z-Axis
	ImGui::SliderFloat("Rotation Angle (Z)", &meshData.rotationZ, -180.0f, 180.0f);
	Eigen::MatrixXd rotatedVerticesZ = rotateViaZAxis(rotatedVerticesY, degreesToRadians(meshData.rotationZ));

	mesh->updateVertexPositions(rotatedVerticesZ);
}

void convexCombination(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	ImGui::SliderFloat("Rotation Angle (X)", &meshData.rotationX, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &meshData.rotationY, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &meshData.rotationZ, -180.0f, 180.0f);

	ImGui::InputFloat("Scaling X", &meshData.scaleX, 0.05f, 0.5f, "%.2f");
	ImGui::InputFloat("Scaling Y", &meshData.scaleY, 0.05f, 0.5f, "%.2f");
	ImGui::InputFloat("Scaling Z", &meshData.scaleZ, 0.05f, 0.5f, "%.2f");

	ImGui::Dummy(ImVec2(0.0f, 20.0f));

	ImGui::BeginDisabled(std::abs((meshData.scaleX + meshData.scaleY + meshData.scaleZ) - 1.0f) > 1e-6);

	if (ImGui::Button(std::format("Apply ConvexCombinataion", mesh_name).c_str()))
	{

		Eigen::MatrixXd convex = convexCombinationXY(
			meshData.vertices,
			meshData.rotationX,
			meshData.rotationY,
			meshData.scaleX);

		mesh->updateVertexPositions(convex);
	}
	ImGui::SameLine();
	if (ImGui::Button("Apply Normalized ConvexCombination"))
	{

		Eigen::MatrixXd convex = convexCombinationOrthoXY(
			meshData.vertices,
			meshData.rotationX,
			meshData.rotationY,
			meshData.scaleX);

		mesh->updateVertexPositions(convex);
	}

	ImGui::EndDisabled();
}

void optimalRotation(std::string mesh_name)
{
	MeshData &meshData = Meshes[mesh_name];
	polyscope::SurfaceMesh *mesh = polyscope::getSurfaceMesh(mesh_name);

	ImGui::Text("Amount of Rotations: %ld", rotations.size());

	ImGui::SliderFloat("Rotation Angle (X)", &rotationXOptimization, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &rotationYOptimization, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &rotationZOptimization, -180.0f, 180.0f);

	if (ImGui::Button("Reset Rotations"))
	{
		rotations.clear();
	}
	ImGui::SameLine();
	if (ImGui::Button("Add Rotation"))
	{
		rotations.push_back(rotationMatrix(
			degreesToRadians(rotationXOptimization),
			degreesToRadians(rotationYOptimization),
			degreesToRadians(rotationZOptimization)));
	}

	if (ImGui::Button("Generate Random Rotations"))
	{
		addRandomRotations(1);
	}

	if (ImGui::Button("Optimize"))
	{
		RotationOptimizer optimizer(rotations, 1, 1000, 1e-6);
		Eigen::MatrixXd initialGuess = Eigen::MatrixXd::Identity(3, 3);
		Eigen::MatrixXd optimalRotation = optimizer.optimizeOnManifold(
			initialGuess,
			squaredChordalDistance,
			squaredChordalDistanceGradient);

		Eigen::MatrixXd rotated = meshData.vertices * optimalRotation;
		mesh->updateVertexPositions(rotated);
	}
}

void displayFlags()
{
	ImGui::SliderFloat("Rotation Angle (X)", &rotationXFlag, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Y)", &rotationYFlag, -180.0f, 180.0f);
	ImGui::SliderFloat("Rotation Angle (Z)", &rotationZFlag, -180.0f, 180.0f);

	Eigen::Matrix3d rotation = rotationMatrix(
		degreesToRadians(rotationXFlag),
		degreesToRadians(rotationYFlag),
		degreesToRadians(rotationZFlag));

	displayLineFromMatrix(rotation);
	displayPlaneFromMatrix(rotation);
}

void generateRandomRotationsAndDisplay(int numOfRotations)
{
	rotations.clear();
	rotationsPoints.clear();

	// std::cout << "Generating " << numOfRotations << " random rotations" << std::endl;

	for (int i = 0; i < numOfRotations; ++i)
	{
		Eigen::Matrix3d rotation = generateRandomRotation();
		rotations.push_back(rotation);
		Eigen::Vector3d rotationPoint = RotationAsPoint(rotation);
		rotationsPoints.push_back(rotationPoint);
	}

	auto pointCloud = polyscope::registerPointCloud("Rotations Points", rotationsPoints);

	pointCloud->setPointRadius(0.01);
	pointCloud->setPointColor({1.0, 0.0, 0.0});
}

void addRandomRotations(int numOfRotations)
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

void displayLineFromMatrix(const Eigen::Matrix3d &matrix)
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

	auto *line = polyscope::registerCurveNetwork("Line Rotation Flag", points, edges);
	line->setRadius(0.01);
}

void displayPlaneFromMatrix(const Eigen::Matrix3d &matrix)
{

	Eigen::Vector3d u = matrix.col(0);
	Eigen::Vector3d v = matrix.col(1);

	std::vector<Eigen::Vector3d> vertices = {
		u + v,
		u - v,
		-u - v,
		-u + v};

	std::vector<std::array<size_t, 3>> faces = {
		{0, 1, 2},
		{0, 2, 3}};

	std::vector<std::array<double, 3>> psVertices;
	for (const auto &vertex : vertices)
	{
		psVertices.push_back({vertex.x(), vertex.y(), vertex.z()});
	}

	polyscope::registerSurfaceMesh("Plane Rotation Flag", psVertices, faces);
}